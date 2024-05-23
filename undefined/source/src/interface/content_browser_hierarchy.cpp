#include "interface/content_browser_hierarchy.h"

void ContentBrowserHierarchy::Update()
{
    ImGui::BeginChild("Hierarchy", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 0), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);

    DisplayDirectories(pPath);

    ImGui::EndChild();
}

void ContentBrowserHierarchy::DisplayDirectories(const std::filesystem::path& path)
{
    mName = path.filename().string();
    pIsDirectory = std::filesystem::is_directory(path);

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

    SetupTreeNodeFlags(flags, path);

    ImGui::Image(Utils::IntToPointer<ImTextureID>(ResourceManager::Get<Texture>("imgui/folder.png")->GetID()), ImVec2(15, 15));
    ImGui::SameLine();

    if (ImGui::TreeNodeEx(mName.c_str(), flags))
    {
        RightClickInteractions(path);
        if (ImGui::IsItemHovered() && !ImGui::IsItemToggledOpen() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            std::string file = "start explorer ";
            file += '"' + absolute(path).string() + '"';
            system(file.c_str());
        }

        if (pIsDirectory)
        {
            if (!ImGui::IsItemToggledOpen() && ImGui::IsItemClicked(ImGuiMouseButton_Left))
            {
                pCurrentPath = path;
            }

            //For every folder we call the function to display what's inside
            for (const auto& entry : std::filesystem::directory_iterator(path))
            {
                if (entry.is_directory())
                {
                    DisplayDirectories(entry);
                }
            }
        }
        ImGui::TreePop();
    }

    else
    {
        if (!ImGui::IsItemToggledOpen() && ImGui::IsItemClicked(ImGuiMouseButton_Left))
        {
            pCurrentPath = path;
        }
        RightClickInteractions(path);
    }
}

void ContentBrowserHierarchy::SetupTreeNodeFlags(ImGuiTreeNodeFlags& flags, const std::filesystem::path& path)
{
    if (pIsDirectory)
    {
        bool isAnyFolder = false;
        for (const auto& entry : std::filesystem::directory_iterator(path))
        {
            if (entry.is_directory())
            {
                isAnyFolder = true;
                flags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                break;
            }

            else
            {
                continue;
            }
        }

        if (!isAnyFolder)
        {
            flags |= ImGuiTreeNodeFlags_Leaf;
        }

        if (pCurrentPath == path)
        {
            flags |= ImGuiTreeNodeFlags_Selected;
        }

        if (path == pPath)
        {
            flags |= ImGuiTreeNodeFlags_DefaultOpen;
        }
    }
}

void ContentBrowserHierarchy::RightClickInteractions(const std::filesystem::path& path)
{
    if (pRenamingPath == path)
    {
        mName = "##";
    }

    RightClickWindow(path);
    
    if (pRenamingPath == path)
    {
        ImGui::SameLine();
        RenameItem();
    }
}