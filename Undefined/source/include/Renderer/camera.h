#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "toolbox/Matrix4x4.h"
#include "Vector3.h"

class Camera
{
public:
    Camera(float width, float height);
    ~Camera() = default;

    Matrix4x4 ProjectionMatrix(float fovY, float aspect, float far, float near);
    Matrix4x4 ViewMatrix(const Vector3& up, const Vector3& eye, const Vector3& lookAt);

    const Matrix4x4& GetVP();

    void Update();

    void ProcessInput(GLFWwindow* window);

    Vector3 Eye;
    Vector3 LookAt;
    Vector3 Up;

    float Yaw;
    float Pitch;

    bool FirstMouse;
    float LastX;
    float LastY;

    bool IsMouseForCam;

private:
    Matrix4x4 m_VP;

    Matrix4x4 View;
    Matrix4x4 Perspective;

    float Width;
    float Height;
};

