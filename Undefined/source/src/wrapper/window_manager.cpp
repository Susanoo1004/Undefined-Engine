#include "wrapper/window_manager.h"

#include <iostream>

WindowManager::WindowManager()
{
    mWindow = NULL;
}

WindowManager::~WindowManager()
{
    glfwDestroyWindow(mWindow);
}

bool WindowManager::SetupGlfw()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwSetErrorCallback(
        [](int error, const char* description)
        {
            std::cerr << "GLFW error " << error << ": " << description << std::endl;
        }
    );

    if (!glfwInit())
    {
        return false;
    }

    return true;
}

void WindowManager::CreateWindow(int width, int height)
{
    mWindow = glfwCreateWindow(width, height, "Undefined Engine", nullptr, nullptr);
}

void WindowManager::SetupWindow()
{
    glfwMakeContextCurrent(mWindow);

    // gladLoadGL();

    glfwSwapInterval(1); // Enable vsync
}

void WindowManager::GetFramebufferSize(int& display_width, int& display_height)
{
    glfwGetFramebufferSize(mWindow, &display_width, &display_height);
}

GLFWwindow* WindowManager::GetWindowVar()
{
    return mWindow;
}

bool WindowManager::IsWindowOpen()
{
    return !glfwWindowShouldClose(mWindow) && glfwGetKey(mWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}

void WindowManager::SwapBuffers()
{
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

void WindowManager::SetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun callback)
{
    glfwSetCursorPosCallback(window, callback);
}
