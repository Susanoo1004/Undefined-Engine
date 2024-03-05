#include "wrapper/window_manager.h"

#include <iostream>
#include <toolbox/calc.h>

#include "service_locator.h"

WindowManager::WindowManager()
    : mCam(1200,800)
{
    mWindow = NULL;
}

WindowManager::~WindowManager()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
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

Camera* WindowManager::GetCamera()
{
    return &mCam;
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

void WindowManager::WindowSizeCallback(GLFWwindow* , int width, int height)
{
    ServiceLocator::Get<WindowManager>()->Width = width;
    ServiceLocator::Get<WindowManager>()->Height = height;

    Matrix4x4 result;
    Matrix4x4::ProjectionMatrix(calc::PI / 2, (float)ServiceLocator::Get<WindowManager>()->Width / (float)ServiceLocator::Get<WindowManager>()->Height, 0.1f, 20.0f, result);
    ServiceLocator::Get<WindowManager>()->GetCamera()->SetPerspective(result);
    glViewport(0, 0, ServiceLocator::Get<WindowManager>()->Width, ServiceLocator::Get<WindowManager>()->Height);
}

void WindowManager::SetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun callback)
{
    glfwSetWindowSizeCallback(window, callback);
}
