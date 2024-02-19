#include "Wrapper/wrapper_glfw.h"

#include <iostream>

bool WrapperGLFW::SetupGlfw()
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
        return false;

    return true;
}

void WrapperGLFW::CreateWindow(int width, int height)
{
    window = glfwCreateWindow(width, height, "Undefined Engine", nullptr, nullptr);
}

void WrapperGLFW::SetupWindow()
{
    glfwMakeContextCurrent(window);

    // gladLoadGL();

    glfwSwapInterval(1); // Enable vsync
}

void WrapperGLFW::GetFramebufferSize(int& display_width, int& display_height)
{
    glfwGetFramebufferSize(window, &display_width, &display_height);
}

GLFWwindow* WrapperGLFW::GetWindowVar()
{
    return window;
}

void WrapperGLFW::SwapBuffers()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool WrapperGLFW::IsWindowOpen()
{
    return !glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}

void WrapperGLFW::SetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun callback)
{
    glfwSetCursorPosCallback(window, callback);
}