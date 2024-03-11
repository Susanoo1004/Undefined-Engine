#include <glad/glad.h>

#include "application.h"

#include "memory_leak.h"

#include "resources/resource_manager.h"

#include "utils/flag.h"

#include "service_locator.h"

#include "interface/interface.h"

int main()
{
    ServiceLocator::Setup();

    Application app;

    Window* wManager = ServiceLocator::Get<Window>();
    Renderer* renderer = ServiceLocator::Get<Renderer>();

    if (!wManager->SetupGlfw())
    {
        return 1;
    }

    wManager->CreateWindow(1200, 800);

    if (wManager->GetWindowVar() == nullptr)
    {
        return 1;
    }

    wManager->SetupWindow();

    renderer->Init();

    ServiceLocator::Get<InputManager>()->SetCursorPosCallback(wManager->GetWindowVar(), Camera::MouseCallback);

    KeyInput::SetupKeyInputs();

    Window::SetWindowSizeCallback(wManager->GetWindowVar(), Window::WindowSizeCallback);

    // app.SetupImGui(window);

    renderer->Debug.DebugInit();

    app.Init();

    // Let the window open until we press escape or the window should close
    while (wManager->IsWindowOpen())
    {

        // app.StartImGuiFrame();

        // Imgui stuff here is called from the main program loop and called from the window loop itself when the window is closed and the window 
        // app.ShowImGuiControls();

        app.Update();

        // Rendering 
        // app.Render(window);

        wManager->SwapBuffers();
        renderer->ClearBuffer();
    }

    ServiceLocator::CleanServiceLocator();
    ResourceManager::UnloadAll();
    Interface::Delete();

    Logger::Stop();
    MemoryLeak::EndMemoryLeak();

    return 0;
}
