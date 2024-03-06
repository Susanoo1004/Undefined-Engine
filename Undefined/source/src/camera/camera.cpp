#include "camera/camera.h"

#include <numbers>
#include <iostream>

#include "service_locator.h"

#define PI std::numbers::pi_v<float>

Camera* Camera::sCamPtr;

Camera::Camera(float width, float height)
    : mWidth(width), mHeight(height)
{
    Eye = Vector3(0, 0, -1);
    LookAt = Vector3(0, 0, 1);
    Up = Vector3(0, 1, 0);

    Matrix4x4::ProjectionMatrix(PI / 2, mWidth / mHeight, 0.1f, 20.0f, mPerspective);

    sCamPtr = this;

    std::vector<int> keys = { GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT, GLFW_MOUSE_BUTTON_RIGHT };

    ServiceLocator::Get<InputManager>()->CreateKeyInput("editorCameraInput", keys);
}

Camera::~Camera()
{

}

void Camera::SetPerspective(Matrix4x4& perspectiveMat)
{
    mPerspective = perspectiveMat;
}

const Matrix4x4& Camera::GetVP()
{
    return mVP;
}

void Camera::Update()
{
    Matrix4x4::ViewMatrix(Eye, Eye + LookAt, Up, mView);
    mVP = mPerspective * mView;
}

void Camera::ProcessInput(GLFWwindow*)
{

    const float cameraSpeed = 0.05f; // adjust accordingly

    std::shared_ptr<KeyInput> editorCameraInput = ServiceLocator::Get<InputManager>()->GetKeyInput("editorCameraInput");

    if (editorCameraInput->GetIsKeyDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
        IsMouseForCam = true;
    }
    else
    {
        IsMouseForCam = false;
    }

    if (editorCameraInput->GetIsKeyDown(GLFW_KEY_W))
    {
        Eye += cameraSpeed * LookAt;
    }
    if (editorCameraInput->GetIsKeyDown(GLFW_KEY_S))
    {
        Eye -= cameraSpeed * LookAt;
    }
    if (editorCameraInput->GetIsKeyDown(GLFW_KEY_A))
    {
        Eye -= Vector3::Cross(LookAt, Up).Normalized() * cameraSpeed;
    }
    if (editorCameraInput->GetIsKeyDown(GLFW_KEY_D))
    {
        Eye += Vector3::Cross(LookAt, Up).Normalized() * cameraSpeed;
    }
    if (editorCameraInput->GetIsKeyDown(GLFW_KEY_SPACE))
    {
        Eye.y += cameraSpeed;
    }
    if (editorCameraInput->GetIsKeyDown(GLFW_KEY_LEFT_SHIFT))
    {
        Eye.y -= cameraSpeed;
    }

}

void Camera::MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    InputManager* inputManager = ServiceLocator::Get<InputManager>();

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (sCamPtr->IsMouseForCam)
    {
        inputManager->SetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        inputManager->SetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        sCamPtr->IsFirstMouse = true;
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
