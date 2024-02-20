#include "camera/camera.h"

#include <numbers>
#include <iostream>

#define PI std::numbers::pi_v<float>

Camera* Camera::sCamPtr;

Camera::Camera(float width, float height)
    : mWidth(width), mHeight(height)
{
    eye = Vector3(0, 0, -1);
    lookAt = Vector3(0, 0, 1);
    up = Vector3(0, 1, 0);

    mPerspective = ProjectionMatrix(PI / 2, mWidth / mHeight, 0.1f, 20.0f);

    sCamPtr = this;
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
    mView = ViewMatrix(up, eye, eye + lookAt);
    mVP = mPerspective * mView;
}

void Camera::ProcessInput(GLFWwindow* window)
{
    const float cameraSpeed = 0.05f; // adjust accordingly

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        eye += cameraSpeed * lookAt;
    }   
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        eye -= cameraSpeed * lookAt;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        eye -= Vector3::Cross(lookAt, up).Normalized() * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        eye += Vector3::Cross(lookAt, up).Normalized() * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        isMouseForCam = !isMouseForCam;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        eye.y += cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        eye.y -= cameraSpeed;
    }

}

void Camera::MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (sCamPtr->isMouseForCam)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        return;
    }
    if (sCamPtr->firstMouse)
    {
        sCamPtr->lastX = xpos;
        sCamPtr->lastY = ypos;
        sCamPtr->firstMouse = false;
    }

    float xoffset = xpos - sCamPtr->lastX;
    float yoffset = sCamPtr->lastY - ypos;
    sCamPtr->lastX = xpos;
    sCamPtr->lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    sCamPtr->yaw += xoffset;
    sCamPtr->pitch += yoffset;

    if (sCamPtr->pitch > 89.0f)
    {
        sCamPtr->pitch = 89.0f;
    }
    if (sCamPtr->pitch < -89.0f)
    {
        sCamPtr->pitch = -89.0f;
    }

    std::cout << "scamptr : " << sCamPtr->yaw << " ; " << sCamPtr->pitch << std::endl;

    Vector3 direction;
    direction.x = cosf((sCamPtr->yaw * (PI / 180.f))) * cosf((sCamPtr->pitch * (PI / 180.f)));
    direction.y = sinf((sCamPtr->pitch * (PI / 180.f)));
    direction.z = sinf((sCamPtr->yaw * (PI / 180.f))) * cosf((sCamPtr->pitch * (PI / 180.f)));
    sCamPtr->lookAt = direction.Normalized();
}
