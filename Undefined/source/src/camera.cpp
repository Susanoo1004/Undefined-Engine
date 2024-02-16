#include "camera.h"

#include <numbers>
#include <iostream>

#define PI std::numbers::pi_v<float>

Camera::Camera(float width, float height)
    : mWidth(width), mHeight(height)
{
    Eye = Vector3(0, 0, -1);
    LookAt = Vector3(0, 0, 1);
    Up = Vector3(0, 1, 0);

    mPerspective = ProjectionMatrix(PI / 2, mWidth / mHeight, 0.1f, 20.0f);
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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Eye += cameraSpeed * LookAt;
        std::cout << "aaaaaa" << std::endl;
    }   
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Eye -= cameraSpeed * LookAt;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Eye -= Vector3::Cross(LookAt, Up).Normalized() * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Eye += Vector3::Cross(LookAt, Up).Normalized() * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        IsMouseForCam = !IsMouseForCam;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        Eye.y += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        Eye.y -= cameraSpeed;
}