#include "interface/interface.h"

#include "utils/utils.h"
#include "service_locator.h"

#include "interface/fps_graph.h"
#include "interface/content_browser.h"
#include "interface/inspector.h"
#include "world/scene_manager/scene.h"

void Interface::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io.Fonts->AddFontDefault();

    constexpr const char* glslVersion = "#version 450";

    ImGui_ImplGlfw_InitForOpenGL(ServiceLocator::Get<Window>()->GetWindowVar(), true);
    ImGui_ImplOpenGL3_Init(glslVersion);

    std::vector<int> keys = { GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT, GLFW_MOUSE_BUTTON_RIGHT };
    ServiceLocator::Get<InputManager>()->CreateKeyInput("editorCameraInput", keys);

    CreateEditorViewport();
}

void Interface::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Interface::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    ServiceLocator::Get<Window>()->SetupWindow();
}

void Interface::BeginDockSpace()
{
    static bool dockspaceOpen = true;
    static bool optFullscreenPersistant = true;
    const bool optFullscreen = optFullscreenPersistant;

    ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
    if (optFullscreen)
        dockspaceFlags |= ImGuiDockNodeFlags_PassthruCentralNode;

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (optFullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
    }

    // Begin docking layout
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, windowFlags);
    if (optFullscreen)
        ImGui::PopStyleVar(3);

    const ImGuiID dockspaceId = ImGui::GetID("DockSpace");
    ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);
}

void Interface::Update(Scene scene)
{
    NewFrame();
    BeginDockSpace();

    FPSGraph::ShowWindow();
    ContentBrowser::DisplayWindow();
    Inspector::ShowWindow(scene);

    for (int i = 0; i < EditorViewports.size(); i++)
    {
        EditorViewports[i]->ShowWindow();
    }

    ImGui::End();
}

void Interface::Delete()
{
    FPSGraph::Delete();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyPlatformWindows();
    ImGui::DestroyContext();
}

UNDEFINED_ENGINE void Interface::CreateEditorViewport()
{
    Framebuffer* framebuffer = Framebuffer::Create<2>(200, 200);
    Camera* camera = new Camera(200, 200);

    EditorViewports.push_back(new EditorViewport(framebuffer, camera));
}

UNDEFINED_ENGINE void Interface::DeleteEditorViewport(int ID)
{
    std::vector<EditorViewport*>::iterator it = EditorViewports.begin();

    for (EditorViewport* e : EditorViewports)
    {
        if (ID == e->GetEditorID())
        {
            EditorViewports.erase(it);
            delete e;
            break;
        }

        it++;
    }
}
