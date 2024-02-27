#include "interface/interface.h"
#include "service_locator.h"


Interface::~Interface()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyPlatformWindows();
    ImGui::DestroyContext();
}

void Interface::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io.Fonts->AddFontDefault();

    constexpr const char* glslVersion = "#version 330";

    ImGui_ImplGlfw_InitForOpenGL(ServiceLocator::Get<WindowManager>()->GetWindowVar(), true);
    ImGui_ImplOpenGL3_Init(glslVersion);
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
    ServiceLocator::Get<WindowManager>()->SetupWindow();
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



void Interface::Update()
{
    NewFrame();
    BeginDockSpace();

    ContentBrowser();
    Inspector();

    ImGui::ShowDemoWindow();

    ImGui::End();
    Render();
}


void Interface::ContentBrowserDirectory(const std::filesystem::path& path)
{
    bool isDirectory = std::filesystem::is_directory(path);
    
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_FramePadding;

    if (isDirectory)
    {
        flags |= ImGuiTreeNodeFlags_None;
    }

    else
    {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    if (ImGui::TreeNodeEx(path.filename().string().c_str(), flags))
    {
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::Button("Open in explorer"))
            {
                std::string explorer = "start explorer /select," + absolute(path).string();
                system(explorer.c_str());
            }
            ImGui::EndPopup();
        }

        if (isDirectory)
        {
            for (const auto& entry : std::filesystem::directory_iterator(path))
            {
                ContentBrowserDirectory(entry);
            }
        }
        ImGui::TreePop();
    }

    else
    {
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::Button("Open in explorer"))
            {
                std::string explorer = "start explorer /select," + absolute(path).string();
                system(explorer.c_str());
            }
            ImGui::EndPopup();
        }
    }
}

void Interface::ContentBrowser()
{
    ImGui::Begin("Content Browser");

    ImGui::BeginChild("Hierarchy", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 0), ImGuiChildFlags_Border | 
      ImGuiChildFlags_ResizeX);

    ContentBrowserDirectory("../Editor/assets");

    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginChild("Repertory", ImVec2(0, 0), ImGuiChildFlags_Border);
    ImGui::EndChild();

    ImGui::End();
}

void Interface::Inspector()
{
    ImGui::Begin("Inspector");

    ImGui::End();
}