#pragma once

#include "glfw/glfw3.h"

class WrapperGLFW
{
public:
	
    bool SetupGlfw();

    void CreateWindow(int width, int height);

    void SetupWindow();

    void GetFramebufferSize(int &display_width, int &display_height);

    GLFWwindow* GetWindowVar();

    void SwapBuffers();

    bool WindowShouldClose();

private:
    GLFWwindow* window;
};