#pragma once

#include <glfw/glfw3.h>

#include "wrapper/service_type.h"
#include "utils/flag.h"

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

    bool IsWindowOpen();

    void SwapBuffers();

private:
    GLFWwindow* mWindow;
};