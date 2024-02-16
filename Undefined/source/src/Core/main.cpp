#include <glad/glad.h>

#include "application.h"
#include "singleton.h"

int main()
{
    Application app;

    Singleton::Init();

    if (!Singleton::wrapperGLFW->SetupGlfw())
        return 1;

    Singleton::wrapperGLFW->CreateWindow(800, 600);
    if (Singleton::wrapperGLFW->GetWindowVar() == nullptr)
        return 1;

    Singleton::wrapperGLFW->SetupWindow();

    Singleton::wrapperRHI->WrapperInit();

    // glfwSetCursorPosCallback(window, MouseCallback);

    // app.SetupImGui(window);

    // const unsigned int width = app.ScreenWidth;
    // const unsigned int height = app.ScreenHeight;

    Singleton::wrapperRHI->debug.DebugInit();

    app.Init();

    // ////  Let the window open until we press escape or the window should close
    while (Singleton::wrapperGLFW->IsWindowOpen())
    {

        // app.StartImGuiFrame();

        // ////  Imgui stuff here is called from the main program loop and called from the window loop itself when the window is closed and the window 
        // app.ShowImGuiControls();

        app.Update();

        // Rendering 
        // app.Render(window);

        Singleton::wrapperGLFW->SwapBuffers();
        Singleton::wrapperRHI->SetClearColor(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Singleton::Destroy();

    return 0;
}
