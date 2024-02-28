#include <glad/glad.h>

#include "application.h"
#include "memory_leak.h"
#include "Resources/resource_manager.h"
#include "utils/flag.h"
#include "service_locator.h"
#include "wrapper/input_manager.h"
#include "interface/interface.h"

int main()
{
    ServiceLocator::Setup();

    Application app;

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

    //ServiceLocator::Get<InputManager>()->SetCursorPosCallback(ServiceLocator::Get<WindowManager>()->GetWindowVar(), Camera::MouseCallback);

    KeyInput::SetupKeyInputs();

    // app.SetupImGui(window);

    ServiceLocator::Get<Renderer>()->debug.DebugInit();

    app.Init();


    // Let the window open until we press escape or the window should close

    while (ServiceLocator::Get<WindowManager>()->IsWindowOpen())
    {

        // app.StartImGuiFrame();

        // Imgui stuff here is called from the main program loop and called from the window loop itself when the window is closed and the window 
        // app.ShowImGuiControls();

        app.Update();

        // Rendering 
        // app.Render(window);

        ServiceLocator::Get<WindowManager>()->SwapBuffers();
        ServiceLocator::Get<Renderer>()->SetClearColor(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    ServiceLocator::CleanServiceLocator();
    ResourceManager::UnloadAll();
    Interface::Delete();

    Logger::Stop();
    MemoryLeak::EndMemoryLeak();

    return 0;
}
