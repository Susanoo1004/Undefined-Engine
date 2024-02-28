#include "interface/content_browser.h"

#include <imgui/imgui.h>

void ContentBrowser::Init()
{
    mPath = "../Editor";
    mActualPath = mPath;
}

void ContentBrowser::DisplayDirectory(const std::filesystem::path& path)
{
    bool isDirectory = std::filesystem::is_directory(path);

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

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
        if (ImGui::BeginDragDropSource())
        {
            //ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
            ImGui::Text(path.filename().string().c_str());
            ImGui::EndDragDropSource();
        }

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
            mActualPath = path;
            for (const auto& entry : std::filesystem::directory_iterator(path))
            {
                DisplayDirectory(entry);
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

void ContentBrowser::ShowDirectory(std::filesystem::path actualPath)
{
    for (const auto& entry : std::filesystem::directory_iterator(actualPath))
    {
        //ImGui::ImageButton()
        ImGui::Text(entry.path().filename().string().c_str());
        if(ImGui::GetCursorPosX() < ImGui::GetWindowContentRegionMax().x)
        {
            ImGui::SameLine();
        }
        else
        {
            ImGui::NewLine();
        }
    }
}

void ContentBrowser::ShowWindow()
{
    ImGui::Begin("Content Browser");

    ImGui::BeginChild("Hierarchy", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 0), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);
    DisplayDirectory(mPath);
    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginChild("Repertory", ImVec2(0, 0), ImGuiChildFlags_Border);
    ShowDirectory(mActualPath);
    ImGui::EndChild();

    ImGui::End();
}
