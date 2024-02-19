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

    void ProcessInput(GLFWwindow* window);
    static void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);

    Vector3 Eye;
    Vector3 LookAt;
    Vector3 Up;

    float Yaw = 0.f;
    float Pitch = 0.f;

    bool FirstMouse;
    float LastX;
    float LastY;

    bool IsMouseForCam = false;

    static Camera* sCamPtr;

private:
    Matrix4x4 mVP;

    Matrix4x4 mView;
    Matrix4x4 mPerspective;

    float mWidth;
    float mHeight;
};

