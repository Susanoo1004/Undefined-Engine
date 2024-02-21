#pragma once

#include <glfw/glfw3.h>

class WindowManager
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

    void SetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun callback);


private:
    GLFWwindow* mWindow;
};