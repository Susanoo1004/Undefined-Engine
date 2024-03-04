#pragma once

#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

#include "wrapper/service_type.h"

#include "utils/flag.h"

#include "camera/camera.h"

class UNDEFINED_ENGINE WindowManager : public ServiceType
{
public:
    WindowManager();
    ~WindowManager();

    bool SetupGlfw();

    void CreateWindow(int width, int height);

    void SetupWindow();

    void GetFramebufferSize(int &displayWidth, int &displayHeight);

    GLFWwindow* GetWindowVar();
    Camera* GetCamera();

    bool IsWindowOpen();

    void SwapBuffers();

    int Width = 0;
    int Height = 0;

private:
    GLFWwindow* mWindow;
    Camera mCam;

public:
    static void WindowSizeCallback(GLFWwindow* , int width, int height);

    static void SetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun callback);

};