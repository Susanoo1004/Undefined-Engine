#pragma once

#include <glfw/glfw3.h>

class WindowManager
{
public:
	
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