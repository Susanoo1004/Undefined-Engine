#include "interface/content_browser.h"

#include "Resources/resource_manager.h"
#include <Resources/texture.h>

void ContentBrowser::Init()
{
    mPath = std::filesystem::current_path();
    mCurrentPath = mPath;

    isFolderOpen = false;
    isDirectory = false;
    isAnythingHovered = false;
    isAnythingSelected = false;
    canPop = false;
}

void ContentBrowser::DisplayDirectories(const std::filesystem::path& path)
{
    isDirectory = std::filesystem::is_directory(path);

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
                DisplayDirectories(entry);
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

void ContentBrowser::SetImageValues(std::filesystem::path path)
{
    if (std::filesystem::is_directory(path))
    {
        std::shared_ptr<Texture> folder = ResourceManager::resourceManager.Get<Texture>("assets/imgui/folder.png");

        imageSize = ImVec2((float)folder->GetWidth(), (float)folder->GetHeight());
        imageID = (ImTextureID)folder->GetID();
    }
    else
    {
        if (path.string().ends_with(".jpg") || path.string().ends_with(".png"))
        {
            std::string newName = "assets/" + path.string();

            if (ResourceManager::resourceManager.Contains(newName))
            {
                imageSize = ImVec2(80.f, 80.f);
                imageID = (ImTextureID)ResourceManager::resourceManager.Get<Texture>(newName)->GetID();
            }
        }
        else if (path.string().ends_with(".obj"))
        {
            imageSize = ImVec2(80.f, 80.f);
            imageID = (ImTextureID)ResourceManager::resourceManager.Get<Texture>("assets/imgui/obj_file.png")->GetID();
        }

        else
        {
            std::shared_ptr<Texture> file = ResourceManager::resourceManager.Get<Texture>("assets/imgui/file.png");
            imageSize = ImVec2((float)file->GetWidth(), (float)file->GetHeight());
            imageID = (ImTextureID)file->GetID();
        }
    }
}

void ContentBrowser::ShowText(std::string filename, float size)
{
    //If the text is larger than the image size it wrap on multiple lines else it's centered
    if (ImGui::CalcTextSize(filename.c_str()).x > imageSize.x)
    {
        ImGui::TextWrapped(filename.c_str());
    }

    else
    {
        TextCentered(filename);
    }
}

void ContentBrowser::ShowActualDirectory(std::filesystem::path currentPath)
{
    isAnythingHovered = false;

    // For loop that goes through every file/folder in a path and displays them
    for (const auto& entry : std::filesystem::directory_iterator(currentPath))
    {
        ImGui::SameLine();
        isDirectory = entry.is_directory();

        if (ImGui::GetCursorPosX() <= ImGui::GetContentRegionAvail().x * 2)
        {
            std::string filename = entry.path().filename().string();
 
            SetImageValues(filename);

            ImVec2 childSize = ImVec2(imageSize.x + ImGui::GetStyle().FramePadding.x * 2.f, imageSize.y + ImGui::CalcTextSize(filename.c_str()).y + ImGui::GetStyle().FramePadding.y * 15.f);

            //If the mHoveredPath is the same as the path we're in we change it's style color
            if (mSelectedPath == entry.path())
            {
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.7f, 0.7f, 0.7f, 0.7f));
                canPop = true;
            }

            else if (mHoveredPath == entry.path())
            {
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));
                canPop = true;
            }

            ImGui::BeginChild(filename.c_str(), childSize, ImGuiChildFlags_None, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysUseWindowPadding);
            ImGui::Image(imageID, imageSize);

            //If anything is hovered we set mHoveredPath to the path of the hovered item
            if (ImGui::IsWindowHovered())
            {
                mHoveredPath = entry.path();
                isAnythingHovered = true;
            }

            //If we click on something we select it 
            if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                mSelectedPath = entry.path();
                isAnythingSelected = true;
            }

            //If something is selected and we click somewhere else it deselect it
            if (mSelectedPath == entry.path().string() && !ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                mSelectedPath = "";
                isAnythingSelected = false;
            }

            //If we double click on a folder it shows us what's inside
            if (ImGui::IsWindowHovered() && isDirectory && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                mCurrentPath = entry.path();
                isFolderOpen = false;
            }

            ShowText(filename, imageSize.x);

            ImGui::EndChild();
            if (canPop)
            {
                ImGui::PopStyleColor();
                canPop = false;
            }
        }
        else
        {
            //Create a dummy if we can't create another child for a file/folder so it creates an empty space and go to a new line
            ImGui::Dummy(ImVec2(0, 0));
            ImGui::NewLine();
        }
    }

    //If nothing is hovered we set to path to none so it doesn't hover the last element
    if (!isAnythingHovered)
    {
        mHoveredPath = "";
    }
}

void ContentBrowser::ShowWindow()
{
    ImGui::Begin("Content Browser");

    ImGui::BeginChild("Hierarchy", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 0), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);
    DisplayDirectories(mPath);
    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginChild("Repertory", ImVec2(0, 0), ImGuiChildFlags_Border);
    ShowActualDirectory(mCurrentPath);
    ImGui::EndChild();

    ImGui::End();
}
