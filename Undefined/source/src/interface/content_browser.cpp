#include "interface/content_browser.h"

#include <imgui/imgui.h>

#include "Resources/resource_manager.h"
#include <Resources/texture.h>

void ContentBrowser::Init()
{
    mPath = "../Editor";
    mCurrentPath = mPath;
}

void ContentBrowser::DisplayDirectory(const std::filesystem::path& path)
{
    bool isDirectory = std::filesystem::is_directory(path);

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

    if (isDirectory)
    {
        if (mCurrentPath == path)
        {
            flags |= ImGuiTreeNodeFlags_Selected;
            if (!isFolderOpen)
            {
                ImGui::SetNextItemOpen(true);
                isFolderOpen = true;
            }
        }

        flags |= ImGuiTreeNodeFlags_None;
    }

    else
    {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(0))
    {
        mCurrentPath = path.parent_path();
        isFolderOpen = false;
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

        //Window that pop when we right click on a file with the option to open it in our windows explorer
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
        //Window that pop when we right click on a folder with the option to open it in our windows explorer
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

void ContentBrowser::ShowDirectory(std::filesystem::path currentPath)
{
    //Get the textures for each images we will use
    std::shared_ptr<Texture> file = ResourceManager::resourceManager.Get<Texture>("file");
    std::shared_ptr<Texture> folder = ResourceManager::resourceManager.Get<Texture>("folder");
    bool isAnythingHovered = false;

    // For loop that goes through every file/folder in a path and displays them
    for (const auto& entry : std::filesystem::directory_iterator(currentPath))
    {
        ImGui::SameLine();
        if (ImGui::GetCursorPosX() <= ImGui::GetContentRegionAvail().x * 2)
        {
            bool canPop = false;

            ImVec2 imageSize;
            std::string filename = entry.path().filename().string();
 
            // Check if directory so it can add a directory image and check if it's clicked
            if (entry.is_directory())
            {
                imageSize = ImVec2((float)folder->GetWidth(), (float)folder->GetHeight());

                ImVec2 childSize = ImVec2(imageSize.x + ImGui::GetStyle().FramePadding.x * 2.f, imageSize.y + ImGui::CalcTextSize(filename.c_str()).y + ImGui::GetStyle().FramePadding.y * 15.f);

                if (mHoveredPath == entry.path())
                {
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));
                    canPop = true;
                }

                ImGui::BeginChild(filename.c_str(), childSize, ImGuiChildFlags_None, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
                ImGui::Image((ImTextureID)folder->GetID(), imageSize);

                if (ImGui::IsWindowHovered())
                {
                    mHoveredPath = entry.path();
                    isAnythingHovered = true;
                }

                //If we double click on a folder it shows us what's inside
                if (ImGui::IsWindowHovered() && ImGui::IsMouseDoubleClicked(0))
                {
                    mCurrentPath = entry.path();
                    isFolderOpen = false;
                }
            }
            else
            {
                imageSize = ImVec2((float)file->GetWidth(), (float)file->GetHeight());

                ImVec2 childSize = ImVec2(imageSize.x + ImGui::GetStyle().FramePadding.x * 2.f, imageSize.y + ImGui::CalcTextSize(filename.c_str()).y + ImGui::GetStyle().FramePadding.y * 15.f);

                if (mHoveredPath == entry.path())
                {
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));
                    canPop = true;
                }

                ImGui::BeginChild(filename.c_str(), childSize, ImGuiChildFlags_None, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

                if (ImGui::IsWindowHovered())
                {
                    mHoveredPath = entry.path();
                    isAnythingHovered = true;
                }

                //Setup for the drag and drop system (only for the files)
                if (ImGui::BeginDragDropSource())
                {
                    //ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                    ImGui::Text(filename.c_str());
                    ImGui::EndDragDropSource();
                }

                ImGui::Image((ImTextureID)file->GetID(), imageSize);
            }

            //If the text is larger than the image size it wrap on multiple lines else it's centered
            if (ImGui::CalcTextSize(filename.c_str()).x > imageSize.x)
            {
                ImGui::TextWrapped(filename.c_str());
            }
            else
            {
                TextCentered(filename);
            }

            ImGui::EndChild();
            if (canPop)
            {
                ImGui::PopStyleColor();
            }
        }
        else
        {
            //Create a dummy if we can't create another child for a file/folder so it creates an empty space and go to a new line
            ImGui::Dummy(ImVec2(0, 0));
            ImGui::NewLine();
        }
    }
    if (!isAnythingHovered)
    {
        mHoveredPath = "";
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
    ShowDirectory(mCurrentPath);
    ImGui::EndChild();

    ImGui::End();
}
