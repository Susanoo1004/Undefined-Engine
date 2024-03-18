#include "camera/camera.h"

#include <glfw/glfw3.h>
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

Matrix4x4 Camera::GetView()
{
    return mView;
}

Matrix4x4 Camera::GetProjection()
{
    return mPerspective;
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

void Camera::ProcessInput()
{
    std::shared_ptr<KeyInput> editorCameraInput = ServiceLocator::Get<InputManager>()->GetKeyInput("editorCameraInput");

    mIsMouseForCam = editorCameraInput->GetIsKeyDown(GLFW_MOUSE_BUTTON_RIGHT);

    if (editorCameraInput->GetIsKeyDown(GLFW_KEY_W))
    {
        Eye += LookAt * mCameraSpeed;
    }
    if (editorCameraInput->GetIsKeyDown(GLFW_KEY_S))
    {
        Eye -= LookAt * mCameraSpeed;
    }
    if (editorCameraInput->GetIsKeyDown(GLFW_KEY_A))
    {
        Eye -= Vector3::Cross(LookAt, Up).Normalized() * mCameraSpeed;
    }
    if (editorCameraInput->GetIsKeyDown(GLFW_KEY_D))
    {
        Eye += Vector3::Cross(LookAt, Up).Normalized() * mCameraSpeed;
    }
    if (editorCameraInput->GetIsKeyDown(GLFW_KEY_SPACE))
    {
        Eye.y += mCameraSpeed;
    }
    if (editorCameraInput->GetIsKeyDown(GLFW_KEY_LEFT_SHIFT))
    {
        Eye.y -= mCameraSpeed;
    }
}

void Camera::MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    InputManager* inputManager = ServiceLocator::Get<InputManager>();

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (sCamPtr->mIsMouseForCam)
    {
        inputManager->SetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        inputManager->SetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        sCamPtr->mIsFirstMouse = true;
        return;
    }

    if (sCamPtr->mIsFirstMouse)
    {
        sCamPtr->mLastX = xpos;
        sCamPtr->mLastY = ypos;
        sCamPtr->mIsFirstMouse = false;
    }

    float xoffset = xpos - sCamPtr->mLastX;
    float yoffset = sCamPtr->mLastY - ypos;
    sCamPtr->mLastX = xpos;
    sCamPtr->mLastY = ypos;

    xoffset *= sCamPtr->mMouseSensitivity;
    yoffset *= sCamPtr->mMouseSensitivity;

    sCamPtr->mYaw += xoffset;
    sCamPtr->mPitch += yoffset;

    if (sCamPtr->mPitch > 89.0f)
    {
        sCamPtr->mPitch = 89.0f;
    }
    if (sCamPtr->mPitch < -89.0f)
    {
        sCamPtr->mPitch = -89.0f;
    }

    Vector3 direction;
    direction.x = cosf((sCamPtr->mYaw * (PI / 180.f))) * cosf((sCamPtr->mPitch * (PI / 180.f)));
    direction.y = sinf((sCamPtr->mPitch * (PI / 180.f)));
    direction.z = sinf((sCamPtr->mYaw * (PI / 180.f))) * cosf((sCamPtr->mPitch * (PI / 180.f)));
    sCamPtr->LookAt = direction.Normalized();
}
