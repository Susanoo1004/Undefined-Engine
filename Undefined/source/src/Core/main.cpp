#include <glad/glad.h>

#include "application.h"
#include "service_locator.h"
#include <memory_leak/memory_leak_detector.h>


int main()
{
    MemoryLeakDetector memory;
    Application app;

    ServiceLocator::Setup();

    if (!ServiceLocator::Get<WindowManager>()->SetupGlfw())
    {
        return 1;
    }

    ServiceLocator::Get<WindowManager>()->CreateWindow(800, 600);

    if (ServiceLocator::Get<WindowManager>()->GetWindowVar() == nullptr)
    {
        return 1;
    }

    ServiceLocator::Get<WindowManager>()->SetupWindow();

    ServiceLocator::Get<Renderer>()->Init();

    ServiceLocator::Get<WindowManager>()->SetCursorPosCallback(ServiceLocator::Get<WindowManager>()->GetWindowVar(), Camera::MouseCallback);

    // app.SetupImGui(window);

    // const unsigned int width = app.ScreenWidth;
    // const unsigned int height = app.ScreenHeight;

    ServiceLocator::Get<Renderer>()->debug.DebugInit();

    app.Init();

    // ////  Let the window open until we press escape or the window should close

    while (ServiceLocator::Get<WindowManager>()->IsWindowOpen())
    {

        // app.StartImGuiFrame();

        // ////  Imgui stuff here is called from the main program loop and called from the window loop itself when the window is closed and the window 
        // app.ShowImGuiControls();

        app.Update();

        // Rendering 
        // app.Render(window);

        ServiceLocator::Get<WindowManager>()->SwapBuffers();
        ServiceLocator::Get<Renderer>()->SetClearColor(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    ServiceLocator::CleanServiceLocator();
    Logger::Stop();
    return 0;
}
