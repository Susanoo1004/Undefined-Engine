#include <glad/glad.h>

#include "application.h"
#include "singleton.h"
#include "memory_leak.h"
#include "Resources/resource_manager.h"
#include "utils/flag.h"

int main()
{
    Application app;

    Singleton::Init();

    if (!Singleton::windowManager->SetupGlfw())
    {
        return 1;
    }

    Singleton::windowManager->CreateWindow(800, 600);

    if (Singleton::windowManager->GetWindowVar() == nullptr)
    {
        return 1;
    }

    Singleton::windowManager->SetupWindow();

    Singleton::renderer->Init();

    Singleton::windowManager->SetCursorPosCallback(Singleton::windowManager->GetWindowVar(), Camera::MouseCallback);
  
    // app.SetupImGui(window);

    // const unsigned int width = app.ScreenWidth;
    // const unsigned int height = app.ScreenHeight;

    Singleton::renderer->debug.DebugInit();

    app.Init();

    ////// Let the window open until we press escape or the window should close

    while (Singleton::windowManager->IsWindowOpen())
    {

        // app.StartImGuiFrame();

        // ////  Imgui stuff here is called from the main program loop and called from the window loop itself when the window is closed and the window 
        // app.ShowImGuiControls();

        app.Update();

        // Rendering 
        // app.Render(window);

        Singleton::windowManager->SwapBuffers();
        Singleton::renderer->SetClearColor(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Singleton::Destroy();
    ResourceManager::UnloadAll();
    Logger::Stop();
    MemoryLeak::EndMemoryLeak();

    return 0;
}
