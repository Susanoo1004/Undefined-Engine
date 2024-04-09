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

    /// <summary>
    /// Set the perspective matrix
    /// </summary>
    /// <param name="perspectiveView">: New perspective matrix</param>
    void SetPerspective(const Matrix4x4& perspectiveView);
    /// <summary>
    /// Set this camera as the pointer to the current camera
    /// </summary>
    void SetCurrentCamera();

    /// <summary>
    /// Update the camera
    /// </summary>
    void Update();

    /// <summary>
    /// Get the view matrix
    /// </summary>
    /// <returns>Return the view matrix</returns>
    const Matrix4x4& GetView() const;
    /// <summary>
    /// Get the projection matrix
    /// </summary>
    /// <returns>Return the projection matrix</returns>
    const Matrix4x4& GetProjection() const;
    /// <summary>
    /// Get the VP matrix
    /// </summary>
    /// <returns>Return the VP matrix</returns>
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
    /// <summary>
    /// Callback function for the mouse position to the camera
    /// </summary>
    /// <param name="window">: The pointer to the GLFWwindow used</param>
    /// <param name="xposIn">: Will be fill with mouse posX on screen</param>
    /// <param name="yposIn">: Will be fill with mouse posY on screen</param>
    static void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    /// <summary>
    /// Callback function to modify the speed of the currennt camera using the mouse wheel
    /// </summary>
    /// <param name="window">: The pointer to the GLFWwindow used</param>
    /// <param name="xposIn">: Will be fill with mouse posX on screen</param>
    /// <param name="yposIn">: Will be fill with mouse posY on screen</param>
    static void ChangeSpeedCam(GLFWwindow* window, double xposIn, double yposIn);
    /// <summary>
    /// Manage the input of the current camera
    /// </summary>
    static void ProcessInput();

    static Camera* CurrentCamera;
};
