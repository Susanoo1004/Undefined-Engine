#include "interface/content_browser.h"

#include "interface/content_browser_folders.h"
#include "interface/content_browser_hierarchy.h"

void ContentBrowser::TextCentered(const std::string& text)
{
    auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::TextWrapped(text.c_str());
}

void ContentBrowser::SetImageValues(const std::filesystem::path& path, ImTextureID& mImageID, ImVec2& mImageSize)
{
    if (mIsDirectory)
    {
        std::shared_ptr<Texture> folder = ResourceManager::Get<Texture>("imgui/folder.png");

        mImageSize = ImVec2((float)folder->GetWidth(), (float)folder->GetHeight());
        mImageID = Utils::IntToPointer<ImTextureID>(folder->GetID());
    }
    else
    {
        std::string name = path.generic_string();
        std::string parentName = path.parent_path().filename().generic_string();
        size_t pos = name.find(parentName);
        std::string newName = name.substr(pos);
        
        //If it's a texture we put the image of the texture instead of a basic file image
        if (path.string().ends_with(".jpg") || path.string().ends_with(".png"))
        {
            mImageSize = ImVec2(80.f, 80.f);
            if (ResourceManager::Contains(newName))
            {
                //Disable warning C4312 type cast conversion
                mImageID = Utils::IntToPointer<ImTextureID>(ResourceManager::Get<Texture>(newName)->GetID());
            }
            else
            {
                std::shared_ptr<Texture> file = ResourceManager::Get<Texture>("imgui/file.png");
            }
        }

        else if (path.string().ends_with(".obj"))
        {
            mImageSize = ImVec2(80.f, 80.f);
            mImageID = Utils::IntToPointer<ImTextureID>(ResourceManager::Get<Texture>("imgui/obj_file.png")->GetID());
        }

        else if (path.string().ends_with(".cpp") || path.string().ends_with(".h") || path.string().ends_with(".hpp"))
        {
            mImageSize = ImVec2(80.f, 80.f);
            mImageID = Utils::IntToPointer<ImTextureID>(ResourceManager::Get<Texture>("imgui/visual_studio.png")->GetID());
        }

        else
        {
            std::shared_ptr<Texture> file = ResourceManager::Get<Texture>("imgui/file.png");
            mImageSize = ImVec2((float)file->GetWidth(), (float)file->GetHeight());
            mImageID = Utils::IntToPointer<ImTextureID>(file->GetID());
        }
    }
}

void ContentBrowser::DisplayText(const std::filesystem::path& mFilepath, const std::string& mFilename, ImVec2& mImageSize)
{
    //If the text is larger than the image size it wrap on multiple lines else it's centered
    if (ImGui::CalcTextSize(mFilename.c_str()).x > mImageSize.x)
    {
        if (mRenamingPath != mFilepath)
        {
            ImGui::TextWrapped(mFilename.c_str());
        }
        else
        {
            RenameItemMultiline();
        }
    }

    else
    {
        if (mRenamingPath != mFilepath)
        {
            TextCentered(mFilename);
        }
        else
        {
            RenameItem();
        }
    }
}

void ContentBrowser::InteractionWithItems(const std::filesystem::path& path, bool isBackFolder)
{
    bool isClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left);
    
    //If we hover on a window we add a background color 
    if (ImGui::IsWindowHovered())
    {
        mHoveredPath = path;
        mIsAnythingHovered = true;

        //If we click on a window we select it 
        if (isClicked)
        {
            mSelectedPath = path;
            mIsAnythingSelected = true;
        }

        //If a window is selected and we click somewhere else it deselect it
        if (DoubleClick())
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
                std::string file = "start explorer ";
                file += '"' + absolute(path).string() + '"';
                system(file.c_str());
            }
        }

    }

    //If a window is selected and we click somewhere else it deselect it
    if (mSelectedPath == path && !ImGui::IsWindowHovered() && isClicked)
    {
        mSelectedPath = "";
        mIsAnythingSelected = false;
        mRenamingPath = "";
    }
}

void ContentBrowser::RenameItem()
{
    ImGuiInputTextFlags flags = ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue | 
        ImGuiInputTextFlags_EscapeClearsAll;

    mRenamingName = mRenamingPath.filename().string();
    std::string oldName = mRenamingName;
    std::filesystem::path path = mRenamingPath;

    ImGui::SetKeyboardFocusHere();
    ImGui::PushItemWidth(ImGui::CalcTextSize(mRenamingName.c_str()).x + 5);
    if (ImGui::InputText(oldName.c_str(), &mRenamingName, flags))
    {
        if (std::filesystem::is_directory(mRenamingPath))
        {
            mCurrentPath = (char*)mRenamingName.c_str();
        }

        std::filesystem::path newPath = path.generic_string();
        newPath += "/";
        newPath += (char*)mRenamingName.c_str();

        if (std::filesystem::is_directory(mRenamingPath))
        {
            ResourceManager::RenameFolder(oldName, (char*)mRenamingName.c_str());
            //Change current path to the new path so the back folder does not crash (since the current path does not exist it doesn't have a parent)
            std::string newCurrentPath = mRenamingPath.parent_path().generic_string() + "/";
            newCurrentPath += mRenamingName;
            mCurrentPath = newCurrentPath;
        }

        std::filesystem::rename(mRenamingPath, newPath);
        mRenamingPath = "";
    }
}

void ContentBrowser::RenameItemMultiline()
{
    ImGuiInputTextFlags flags = ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll;
    std::string name = mRenamingPath.filename().string();
    std::string oldName = mRenamingPath.filename().string();
    std::filesystem::path path = mRenamingPath.parent_path();

    char* newName = (char*)name.c_str();

    ImGui::SetKeyboardFocusHere();

    //Change so it goes to another line when you are at the end and not expand it
    if (ImGui::InputTextMultiline("##label", (char*)name.c_str(), 256, ImVec2(50, 40), flags))
    {
        if (std::filesystem::is_directory(mRenamingPath))
        {
            mCurrentPath = (char*)name.c_str();
        }

        std::filesystem::path newPath = path.generic_string();
        newPath += "/";
        newPath += (char*)name.c_str();

        if (std::filesystem::is_directory(mRenamingPath))
        {
            ResourceManager::RenameFolder(oldName, (char*)name.c_str());
            //Change current path to the new path so the back folder does not crash (since the current path does not exist it doesn't have a parent)
            std::string newCurrentPath = mRenamingPath.parent_path().generic_string() + "/";
            newCurrentPath += newName;
            mCurrentPath = newCurrentPath;
        }

        std::filesystem::rename(mRenamingPath, newPath);
        mRenamingPath = "";
    }
}

void ContentBrowser::RightClickWindow(const std::filesystem::path& path)
{
    if (ImGui::BeginPopupContextItem(path.string().c_str()))
    {
        if (ImGui::Button("Open in explorer"))
        {
            std::string explorer = "start explorer /select,";
            explorer += absolute(path).string();
            system(explorer.c_str());
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Button("Rename"))
        {
            mRenamingPath = path;
            mSelectedPath = mRenamingPath;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void ContentBrowser::DisplayWindow()
{
    ImGui::Begin("Content Browser");

    ContentBrowserHierarchy::Update();
    ContentBrowserFolders::Update();

    ImGui::End();
}

bool ContentBrowser::DoubleClick()
{
    clickCount = ImGui::GetMouseClickedCount(ImGuiMouseButton_Left);

    return clickCount && (clickCount % 2 == 0);
}