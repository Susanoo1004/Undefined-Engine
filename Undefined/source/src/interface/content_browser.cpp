#include "interface/content_browser.h"

#include <imgui/imgui.h>

#include "Resources/resource_manager.h"
#include <Resources/texture.h>

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
        //Setup for the drag and drop system
        if (ImGui::BeginDragDropSource())
        {
            //ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
            ImGui::Text(path.filename().string().c_str());
            ImGui::EndDragDropSource();
        }

        //Window that pop when we right click on a file so we can open it in our windows explorer
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

            //For every folder we call the function to display what's inside
            for (const auto& entry : std::filesystem::directory_iterator(path))
            {
                DisplayDirectory(entry);
            }
        }

        ImGui::TreePop();
    }

    else
    {
        //Window that pop when we right click on a folder so we can open it in our windows explorer
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

void ContentBrowser::TextCentered(std::string text)
{
    auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::TextWrapped(text.c_str());
}

void ContentBrowser::ShowDirectory(std::filesystem::path actualPath)
{
    //Get the textures for each images we will use
    std::shared_ptr<Texture> file = ResourceManager::resourceManager.Get<Texture>("file");
    std::shared_ptr<Texture> folder = ResourceManager::resourceManager.Get<Texture>("folder");

    // For loop that goes through every file/folder in a path and displays them
    for (const auto& entry : std::filesystem::directory_iterator(actualPath))
    {
        ImGui::SameLine();
        if (ImGui::GetCursorPosX() <= ImGui::GetContentRegionAvail().x * 2)
        {
            ImVec2 imageSize;
            std::string filename = entry.path().filename().string();
 
            // Check if directory so it can add a directory image and check if it's clicked
            if (entry.is_directory())
            {
                imageSize = ImVec2((float)folder->GetWidth(), (float)folder->GetHeight());
                ImGui::BeginChild(filename.c_str(), ImVec2(imageSize.x + 20, imageSize.y + 40));
                ImGui::Image((ImTextureID)folder->GetID(), imageSize);

                //If we double click on a folder it shows us what's inside
                if (ImGui::IsWindowHovered() && ImGui::IsMouseDoubleClicked(0))
                {
                    mActualPath = entry.path();
                }
            }
            else
            {
                imageSize = ImVec2((float)file->GetWidth(), (float)file->GetHeight());
                ImGui::BeginChild(filename.c_str(), ImVec2(imageSize.x + 20, imageSize.y + 40));

                //Setup for the drag and drop system (only for the files)
                if (ImGui::BeginDragDropSource())
                {
                    //ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                    ImGui::Text(filename.c_str());
                    ImGui::EndDragDropSource();
                }

                ImGui::Image((ImTextureID)file->GetID(), imageSize);
            }

            TextCentered(filename);
            ImGui::EndChild();
        }
        else
        {
            //Create a dummy if we can't create another child for a file/folder so it creates an empty space and go to a new line
            ImGui::Dummy(ImVec2(0, 0));
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
