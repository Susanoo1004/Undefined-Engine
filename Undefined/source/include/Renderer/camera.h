#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "toolbox/Matrix4x4.h"
#include "toolbox/Vector3.h"

class Camera
{
public:
    Camera(float width, float height);
    ~Camera() = default;

    Matrix4x4 ProjectionMatrix(float fovY, float aspect, float far, float near);
    Matrix4x4 ViewMatrix(const Vector3& up, const Vector3& eye, const Vector3& lookAt);

    const Matrix4x4& GetVP();

    void Update();

    void ProcessInput(GLFWwindow* mWindow);

    Vector3 eye;
    Vector3 lookAt;
    Vector3 up;

    float yaw;
    float pitch;

    bool firstMouse;
    float lastX;
    float lastY;

    bool isMouseForCam;

private:
    Matrix4x4 mVP;

    Matrix4x4 mView;
    Matrix4x4 mPerspective;

    float mWidth;
    float mHeight;
};

