#pragma once

#include "wrapper/service_type.h"

#include "utils/flag.h"

#include "camera/camera.h"

struct GLFWwindow;

class UNDEFINED_ENGINE Window : public ServiceType
{
public:
    Window();
    ~Window();

    void Init();

    void SetupGlfw();

    void CreateWindow(int width, int height);

    void SetupWindow();

    void GetFramebufferSize(int &displayWidth, int &displayHeight);

    GLFWwindow* GetWindowVar();

    bool IsWindowOpen();

    void SwapBuffers();

    int Width = 0;
    int Height = 0;

private:
    GLFWwindow* mWindow;

public:
    static void WindowSizeCallback(GLFWwindow* , int width, int height);
    static void SetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun callback);
    static void ScrollWheelCallback(GLFWwindow* window, GLFWscrollfun callback);

    static void Callbacks();
};