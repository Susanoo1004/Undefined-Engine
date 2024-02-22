#include "camera/camera.h"

#include <numbers>
#include <iostream>

#include <service_locator.h>

#define PI std::numbers::pi_v<float>

Camera* Camera::sCamPtr;

Camera::Camera(float width, float height)
    : mWidth(width), mHeight(height)
{
    Eye = Vector3(0, 0, -1);
    LookAt = Vector3(0, 0, 1);
    Up = Vector3(0, 1, 0);

    mPerspective = ProjectionMatrix(PI / 2, mWidth / mHeight, 0.1f, 20.0f);

    sCamPtr = this;

    std::vector<int> keys = { GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_K, GLFW_KEY_L, GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT };

    ServiceLocator::Get<InputManager>()->CreateKeyInput("cameraInput", keys);
}

Matrix4x4 Camera::ProjectionMatrix(float fovY, float aspect, float far, float near)
{
    float f = 1.0f / tanf((fovY) / 2);
    Matrix4x4 projectionMatrix =
    {
        {f / aspect, 0, 0, 0},
        {0, f, 0, 0},
        {0, 0, (far + near) / (far - near), (2.0f * far * near) / (far - near)},
        {0, 0, -1.0, 0}
    };

    return projectionMatrix;
}

Matrix4x4 Camera::ViewMatrix(const Vector3& up, const Vector3& eye, const Vector3& lookAt)
{
    Vector3 axisZ = (eye - lookAt).Normalized();
    Vector3 axisX = Vector3::Cross(up, axisZ).Normalized();
    Vector3 axisY = Vector3::Cross(axisZ, axisX).Normalized();

    Matrix4x4 viewMatrix =
    {
        { axisX[0], axisX[1], axisX[2], Vector3::Dot(-axisX, eye)},
        { axisY[0], axisY[1], axisY[2], Vector3::Dot(-axisY, eye)},
        { axisZ[0], axisZ[1], axisZ[2], Vector3::Dot(-axisZ, eye)},
        {0, 0, 0, 1}
    };

    return viewMatrix;
}

const Matrix4x4& Camera::GetVP()
{
    return mVP;
}

void Camera::Update()
{
    mView = ViewMatrix(Up, Eye, Eye + LookAt);
    mVP = mPerspective * mView;
}

void Camera::ProcessInput(GLFWwindow* window)
{
    const float cameraSpeed = 0.05f; // adjust accordingly

    InputManager* inputManager = ServiceLocator::Get<InputManager>();

    if (inputManager->GetKeyInput("cameraInput")->GetIsKeyDown(GLFW_KEY_W))
    {
        Eye += cameraSpeed * LookAt;
    }   
    if (inputManager->GetKeyInput("cameraInput")->GetIsKeyDown(GLFW_KEY_S))
    {
        Eye -= cameraSpeed * LookAt;
    }
    if (inputManager->GetKeyInput("cameraInput")->GetIsKeyDown(GLFW_KEY_A))
    {
        Eye -= Vector3::Cross(LookAt, Up).Normalized() * cameraSpeed;
    }
    if (inputManager->GetKeyInput("cameraInput")->GetIsKeyDown(GLFW_KEY_D))
    {
        Eye += Vector3::Cross(LookAt, Up).Normalized() * cameraSpeed;
    }
    if (inputManager->GetKeyInput("cameraInput")->GetIsKeyDown(GLFW_KEY_K) || inputManager->GetKeyInput("cameraInput")->GetIsKeyDown(GLFW_KEY_L))
    {
        IsMouseForCam = !IsMouseForCam;
    }
    if (inputManager->GetKeyInput("cameraInput")->GetIsKeyDown(GLFW_KEY_SPACE))
    {
        Eye.y += cameraSpeed;
    }
    if (inputManager->GetKeyInput("cameraInput")->GetIsKeyDown(GLFW_KEY_LEFT_SHIFT))
    {
        Eye.y -= cameraSpeed;
    }

}

void Camera::MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (sCamPtr->IsMouseForCam)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        return;
    }
    if (sCamPtr->IsFirstMouse)
    {
        sCamPtr->LastX = xpos;
        sCamPtr->LastY = ypos;
        sCamPtr->IsFirstMouse = false;
    }

    float xoffset = xpos - sCamPtr->LastX;
    float yoffset = sCamPtr->LastY - ypos;
    sCamPtr->LastX = xpos;
    sCamPtr->LastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    sCamPtr->Yaw += xoffset;
    sCamPtr->Pitch += yoffset;

    if (sCamPtr->Pitch > 89.0f)
    {
        sCamPtr->Pitch = 89.0f;
    }
    if (sCamPtr->Pitch < -89.0f)
    {
        sCamPtr->Pitch = -89.0f;
    }

    Vector3 direction;
    direction.x = cosf((sCamPtr->Yaw * (PI / 180.f))) * cosf((sCamPtr->Pitch * (PI / 180.f)));
    direction.y = sinf((sCamPtr->Pitch * (PI / 180.f)));
    direction.z = sinf((sCamPtr->Yaw * (PI / 180.f))) * cosf((sCamPtr->Pitch * (PI / 180.f)));
    sCamPtr->LookAt = direction.Normalized();
}
