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

    void SetPerspective(Matrix4x4& perspectiveView);

    void Update();

    void ProcessInput();

    const Matrix4x4& GetVP();

    Vector3 mEye;
    Vector3 mLookAt;
    Vector3 mUp;
  
private:

    Matrix4x4 mVP;
    Matrix4x4 mView;
    Matrix4x4 mPerspective;

    float mWidth;
    float mHeight;

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

    static Camera* CurrentCamera;


private:
    // friend class DirLight;
};
