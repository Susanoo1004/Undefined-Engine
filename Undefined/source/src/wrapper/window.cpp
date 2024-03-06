#include "wrapper/window.h"

#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>
#include <iostream>
#include <toolbox/calc.h>

#include "service_locator.h"

Window::Window()
    : mCam(1200,800)
{
    mWindow = NULL;
}

Window::~Window()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

bool Window::SetupGlfw()
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

void Window::CreateWindow(int width, int height)
{
    mWindow = glfwCreateWindow(width, height, "Undefined Engine", nullptr, nullptr);
}

void Window::SetupWindow()
{
    glfwMakeContextCurrent(mWindow);

    glfwSwapInterval(1); // Enable vsync
}

void Window::GetFramebufferSize(int& display_width, int& display_height)
{
    glfwGetFramebufferSize(mWindow, &display_width, &display_height);
}

GLFWwindow* Window::GetWindowVar()
{
    return mWindow;
}

Camera* Window::GetCamera()
{
    return &mCam;
}

bool Window::IsWindowOpen()
{
    return !glfwWindowShouldClose(mWindow) && glfwGetKey(mWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

void Window::WindowSizeCallback(GLFWwindow* , int width, int height)
{
    Window* w = ServiceLocator::Get<Window>();

    w->Width = width;
    w->Height = height;

    if (w->Height < 0 || w->Width < 0)
    {
        return;
    }

    Matrix4x4 result;
    Matrix4x4::ProjectionMatrix(calc::PI / 2, (float)w->Width / (float)w->Height, 0.1f, 20.0f, result);
    w->GetCamera()->SetPerspective(result);
    glViewport(0, 0, w->Width, w->Height);
}

void Window::SetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun callback)
{
    glfwSetWindowSizeCallback(window, callback);
}
