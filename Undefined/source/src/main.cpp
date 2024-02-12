#include "singleton.h"

int main()
{

    if (!Singleton::wrapperGLFW->SetupGlfw())
        return 1;

    Singleton::wrapperGLFW->CreateWindow(800, 600);
    if (Singleton::wrapperGLFW->GetWindowVar() == nullptr)
        return 1;

    Singleton::wrapperGLFW->SetupWindow();

    // glfwSetCursorPosCallback(window, MouseCallback);

    // app.SetupImGui(window);

    // const unsigned int width = app.ScreenWidth;
    // const unsigned int height = app.ScreenHeight;

    // glEnable(GL_DEBUG_OUTPUT);
    // glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    // glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    //     {
    //         if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
    //             return;

    //         std::cout << message << std::endl;
    //     },
    //     nullptr
    // );

    // glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    // app.Init();

    while (Singleton::wrapperGLFW->WindowShouldClose())
    {

        // app.StartImGuiFrame();

        // ////  Imgui stuff here is called from the main program loop and called from the window loop itself when the window is closed and the window 
        // app.ShowImGuiControls();

        // app.GetCamera().ProcessInput(window);

        // app.Update();

        // Rendering 
        // app.Render(window);

        Singleton::wrapperGLFW->SwapBuffers();
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    return 0;
}