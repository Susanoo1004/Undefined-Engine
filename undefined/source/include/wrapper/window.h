#pragma once

#include "wrapper/service_type.h"

#include "utils/flag.h"

#include "camera/camera.h"

struct GLFWwindow;

/// <summary>
/// Class for our window
/// </summary>
class UNDEFINED_ENGINE Window : public ServiceType
{
public:
    /// <summary>
    /// Constructor of Window
    /// </summary>
    Window();
    /// <summary>
    /// Destructor of Window
    /// </summary>
    ~Window();

    /// <summary>
    /// Initialize the window
    /// </summary>
    void Init();

    /// <summary>
    /// Setup the window library
    /// </summary>
    void SetupWindowLibrary();

    /// <summary>
    /// Create a window
    /// </summary>
    /// <param name="width">: Width of the window</param>
    /// <param name="height">: Height of the window</param>
    void CreateWindow(int width, int height);

    /// <summary>
    /// Setup the window
    /// </summary>
    void SetupWindow();

    /// <summary>
    /// Get the size of the window framebuffer
    /// </summary>
    /// <param name="displayWidth">: Variable where the width will be written</param>
    /// <param name="displayHeight">: Variable where the height will be written</param>
    void GetFramebufferSize(int &displayWidth, int &displayHeight);

    /// <summary>
    /// Get the pointer to the window variable
    /// </summary>
    /// <returns>Return the pointer to the window variable</returns>
    GLFWwindow* GetWindowVar();

    /// <summary>
    /// Check if the window is open
    /// </summary>
    /// <returns>Return either true if it is opne or false</returns>
    bool IsWindowOpen();

    /// <summary>
    /// Swap the window buffers
    /// </summary>
    void SwapBuffers();

    /// <summary>
    /// Width of the window
    /// </summary>
    int Width = 0;
    /// <summary>
    /// Height of the window
    /// </summary>
    int Height = 0;

private:
    /// <summary>
    /// Pointer to the GLFW window
    /// </summary>
    GLFWwindow* mWindow;

public:
    /// <summary>
    /// Callback for the size of the window
    /// </summary>
    /// <param name="width">: New window width</param>
    /// <param name="height">: New window height</param>
    static void WindowSizeCallback(GLFWwindow* , int width, int height);
    /// <summary>
    /// Window API function to execute the window size callback
    /// </summary>
    /// <param name="window">: Pointer to the window API variable</param>
    /// <param name="callback">: Callback function used</param>
    static void SetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun callback);
    /// <summary>
    /// Window API function to execute the scroll wheel callback
    /// </summary>
    /// <param name="window">: Pointer to the window API variable</param>
    /// <param name="callback">: Callback function used</param>
    static void ScrollWheelCallback(GLFWwindow* window, GLFWscrollfun callback);

    /// <summary>
    /// Function that store all our callbacks
    /// </summary>
    static void Callbacks();
};