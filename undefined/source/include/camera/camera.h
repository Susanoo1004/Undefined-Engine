#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "toolbox/Matrix4x4.h"
#include "toolbox/Vector3.h"
#include "utils/flag.h"

class UNDEFINED_ENGINE Camera
{
public:
    Camera(float width, float height);
    ~Camera();

    void SetPerspective(const Matrix4x4& perspectiveView);
    void SetCurrentCamera();

    void Update();

    const Matrix4x4& GetView() const;
    const Matrix4x4& GetProjection() const;
    const Matrix4x4& GetVP() const;

    Vector3 Eye;
    Vector3 LookAt;
    Vector3 Up;
  
    float Width;
    float Height;

private:
    Matrix4x4 mVP;
    Matrix4x4 mView;
    Matrix4x4 mPerspective;

    float mCameraSpeed = 0.05f;
    float mMouseSensitivity = 0.05f;

    float mYaw = 90.f;
    float mPitch = 0.f;

    float mLastX = 0.f;
    float mLastY = 0.f;
    
    bool mIsActive = true;
    bool mIsFirstMouse = true;
    bool mIsMouseForCam = false;

public:
    static void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    static void ChangeSpeedCam(GLFWwindow* window, double xposIn, double yposIn);
    static void ProcessInput();

    static Camera* CurrentCamera;
};
