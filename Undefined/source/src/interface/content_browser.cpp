#include "interface/content_browser.h"

#include "Resources/resource_manager.h"
#include <Resources/texture.h>

#include "utils/utils.h"

void ContentBrowser::Init()
{
    mPath = std::filesystem::current_path();
    mCurrentPath = mPath;
    mBackFolder = "folder";

    mIsFolderOpen = false;
    mIsDirectory = false;
    mIsAnythingHovered = false;
    mIsAnythingSelected = false;
    mCanPop = false;
    mClickCountOffset = 0;
}

void ContentBrowser::DisplayDirectories(const std::filesystem::path& path)
{
    mIsDirectory = std::filesystem::is_directory(path);

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;

    if (mIsDirectory)
    {
        if (mCurrentPath == path)
        {
            flags |= ImGuiTreeNodeFlags_Selected;
        }
    }

    else
    {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    if (ImGui::TreeNodeEx(path.filename().string().c_str(), flags))
    {
        if (!ImGui::IsItemToggledOpen() && ImGui::IsItemClicked(ImGuiMouseButton_Left))
        {
            mCurrentPath = path;
        }

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

        if (mIsDirectory)
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
        //If state changes (if we click on the arrow) then we don't change current path
        if (!ImGui::IsItemToggledOpen() && ImGui::IsItemClicked(ImGuiMouseButton_Left))
        {
            mCurrentPath = path;
        } 

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

void ContentBrowser::SetImageValues(std::filesystem::path path, ImTextureID& imageID, ImVec2& imageSize)
{
    if (mIsDirectory)
    {
        std::shared_ptr<Texture> folder = ResourceManager::resourceManager.Get<Texture>("assets/imgui/folder.png");

        imageSize = ImVec2((float)folder->GetWidth(), (float)folder->GetHeight());
        imageID = Utils::IntToPointer<ImTextureID>(folder->GetID());
    }
    else
    {
        std::string newName = "assets/" + path.string();
        
        if (path.string().ends_with(".jpg") || path.string().ends_with(".png"))
        {

            if (ResourceManager::resourceManager.Contains(newName))
            {
                imageSize = ImVec2(80.f, 80.f);
                imageID = Utils::IntToPointer<ImTextureID>(ResourceManager::resourceManager.Get<Texture>(newName)->GetID());
            }
        }
        else if (path.string().ends_with(".obj"))
        {
            std::string newName = "assets/" + path.string();

            imageSize = ImVec2(80.f, 80.f);
            imageID = Utils::IntToPointer<ImTextureID>(ResourceManager::resourceManager.Get<Texture>("assets/imgui/obj_file.png")->GetID());
        }

        else if (path.string().ends_with(".cpp") || path.string().ends_with(".h") || path.string().ends_with(".hpp"))
        {
            imageSize = ImVec2(80.f, 80.f);
            imageID = Utils::IntToPointer<ImTextureID>(ResourceManager::resourceManager.Get<Texture>("assets/imgui/visual_studio.png")->GetID());
        }

        else
        {
            std::shared_ptr<Texture> file = ResourceManager::resourceManager.Get<Texture>("assets/imgui/file.png");
            imageSize = ImVec2((float)file->GetWidth(), (float)file->GetHeight());
            imageID = Utils::IntToPointer<ImTextureID>(file->GetID());
        }
    }
}

void ContentBrowser::ShowText(std::string filename, ImVec2& imageSize)
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


void ContentBrowser::InteractionWithItems(std::filesystem::path path, bool isBackFolder)
{
    bool isClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left);

    //If we hover on a window we add a background color 
    if (ImGui::IsWindowHovered())
    {
        int clickCount = ImGui::GetMouseClickedCount(ImGuiMouseButton_Left);

        mHoveredPath = path;
        mIsAnythingHovered = true;

        //If we click on a window we select it 
        if (isClicked)
        {
            mSelectedPath = path;
            mIsAnythingSelected = true;
        }

        //If a window is selected and we click somewhere else it deselect it
        if (clickCount && (clickCount % 2 == 0))
        {
            if (mIsDirectory)
            {
                if (!isBackFolder)
                {
                    mCurrentPath = path;
                }

                else
                {
                    mCurrentPath = mCurrentPath.parent_path();
                }
            }
            
            else
            {
                std::string file = '"' + absolute(path).string() + '"';
                system(file.c_str());
            }
        }
    }

    //If a window is selected and we click somewhere else it deselect it
    if (mSelectedPath == path && !ImGui::IsWindowHovered() && isClicked)
    {
        mSelectedPath = "";
        mIsAnythingSelected = false;
    }
}


void ContentBrowser::GoBackFolder(std::filesystem::path path)
{
    mIsAnythingHovered = false;
    mIsDirectory = true;
    ImGui::SameLine();

    if (path != mPath)
    {
        ImTextureID imageID;

        if (mSelectedPath == mBackFolder)
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.7f, 0.7f, 0.7f, 0.7f));
            mCanPop = true;
        }

        else if (mHoveredPath == mBackFolder)
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));
            mCanPop = true;
        }

        ImGui::BeginChild("go back folder", ImVec2(100, 120), ImGuiChildFlags_AlwaysUseWindowPadding);
        imageID = Utils::IntToPointer<ImTextureID>(ResourceManager::resourceManager.Get<Texture>("assets/imgui/folder.png")->GetID());
        ImGui::Image(imageID, ImVec2(80, 80));

        InteractionWithItems(mBackFolder, true);

        TextCentered("../");

        ImGui::EndChild();

        if (mCanPop)
        {
            ImGui::PopStyleColor();
            mCanPop = false;
        }
    }
}

void ContentBrowser::ShowActualDirectory(std::filesystem::path currentPath)
{
    mIsAnythingHovered = false;

    GoBackFolder(currentPath);
    ImGui::SameLine();

    // For loop that goes through every file/folder in a path and displays them
    for (const auto& entry : std::filesystem::directory_iterator(currentPath))
    {
        mIsDirectory = entry.is_directory();

        std::string filename = entry.path().filename().string();
         
        ImVec2 imageSize;
        ImTextureID imageID;

        //Set imageID and imageSize
        SetImageValues(filename, imageID, imageSize);

        ImVec2 childSize = ImVec2(imageSize.x + ImGui::GetStyle().FramePadding.x * 2.f, imageSize.y + ImGui::CalcTextSize(filename.c_str()).y + ImGui::GetStyle().FramePadding.y * 15.f);

        if (mSelectedPath == entry.path())
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.7f, 0.7f, 0.7f, 0.7f));
            mCanPop = true;
        }

        //If the mHoveredPath is the same as the path we're in we change it's style color
        else if (mHoveredPath == entry.path())
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));
            mCanPop = true;
        }

        ImGui::BeginChild(filename.c_str(), childSize, ImGuiChildFlags_None, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysUseWindowPadding);
        ImGui::Image(imageID, imageSize);

        InteractionWithItems(entry);

        ShowText(filename, imageSize);

        ImGui::EndChild();
        if (mCanPop)
        {
            ImGui::PopStyleColor();
            mCanPop = false;
        }

        ImGui::SameLine();

        if(ImGui::GetCursorPosX() > ImGui::GetContentRegionAvail().x * 2)
        {
            //Create a dummy if we can't create another child for a file/folder so it creates an empty space and go to a new line
            ImGui::Dummy(ImVec2(0, 0));
        }
    }

    //If nothing is hovered we set to path to none so it doesn't hover the last element
    if (!mIsAnythingHovered)
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
