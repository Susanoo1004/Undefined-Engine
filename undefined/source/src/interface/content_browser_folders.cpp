#include "interface/content_browser_folders.h"

void ContentBrowserFolders::Update()
{
    ImGui::SameLine();
    ImGui::BeginChild("Repertory", ImVec2(0, 0), ImGuiChildFlags_Border);

    DisplayActualDirectory(mCurrentPath);

    ImGui::EndChild();
}

void ContentBrowserFolders::DisplayActualDirectory(const std::filesystem::path& currentPath)
{
    LoadAll(currentPath);

    // For loop that goes through every file/folder in a path and displays them
    for (int i = 0; i < mCurrPathArray.size(); i++)
    {
        SetAll(i);

        CheckForPushStyle(i);

        DrawFolders(i);

        RightClickWindow(mCurrPathArray[i]);

        ImGui::SameLine();

        CheckForPopStyle();

        if (ImGui::GetCursorPosX() >= ImGui::GetContentRegionAvail().x * 2)
        {
            //Create a dummy if we can't create another child for a file/folder so it creates an empty space and go to a new line
            ImGui::Dummy(ImVec2(0, 0));
        }
    }

    if (!mSelectedPath.empty() && ImGui::IsKeyPressed(ImGuiKey_F2))
    {
        mRenamingPath = mSelectedPath;
    }

    Clear();
}

void ContentBrowserFolders::GoBackFolder(const std::filesystem::path& path)
{
    isBackFolder = true;
    mIsAnythingHovered = false;
    mIsDirectory = true;

    CheckForPushStyle();

    ImGui::SameLine();

    if (path != mPath)
    {
        mImageID = Utils::IntToPointer<ImTextureID>(ResourceManager::Get<Texture>("imgui/folder.png")->GetID());
        ImGui::Image(mImageID, ImVec2(80, 80));

        InteractionWithItems(mBackFolder, true);

        TextCentered("../");

        ImGui::EndChild();

        CheckForPopStyle();
    }
    ImGui::SameLine();

    isBackFolder = false;
}

void ContentBrowserFolders::LoadFolders(const std::filesystem::path& path)
{
    // For loop that goes through every file/folder in a path and displays them
    for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_directory())
        {
            mCurrPathArray.push_back(entry);
        }
    }
}

void ContentBrowserFolders::LoadFiles(const std::filesystem::path& path)
{
    for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(path))
    {
        if (!entry.is_directory())
        {
            mCurrPathArray.push_back(entry);
        }
    }
}

void ContentBrowserFolders::CheckForPushStyle(int i)
{
    if (isBackFolder)
    {
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

        return;
    }

    else
    {
        if (mSelectedPath == mCurrPathArray[i].path())
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.7f, 0.7f, 0.7f, 0.7f));
            mCanPop = true;
        }

        //If the mHoveredPath is the same as the path we're in we change it's style color
        else if (mHoveredPath == mCurrPathArray[i].path())
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));
            mCanPop = true;
        }

        return;
    }
}

void ContentBrowserFolders::CheckForPopStyle()
{
    if (mCanPop)
    {
        ImGui::PopStyleColor();
        mCanPop = false;
    }
}

void ContentBrowserFolders::SetAll(int i)
{
    mIsDirectory = mCurrPathArray[i].is_directory();

    mFilename = mCurrPathArray[i].path().filename().string();
    mFilepath = mCurrPathArray[i].path();

    //Set imageID and imageSize
    SetImageValues(mFilepath, mImageID, mImageSize);

    mChildSize = ImVec2(mImageSize.x + ImGui::GetStyle().FramePadding.x * 2.f,
        mImageSize.y + ImGui::CalcTextSize(mFilename.c_str()).y + ImGui::GetStyle().FramePadding.y * 15.f);

}

void ContentBrowserFolders::LoadAll(const std::filesystem::path& currentPath)
{
    GoBackFolder(currentPath);
    LoadFolders(currentPath);
    LoadFiles(currentPath);
}

void ContentBrowserFolders::Clear()
{
    if (!mIsAnythingHovered)
    {
        mHoveredPath = "";
    }
    else
    {
        mIsAnythingHovered = false;
    }

    mCurrPathArray.resize(0);
    mCurrPathArray.shrink_to_fit();
}

void ContentBrowserFolders::DrawFolders(int i)
{
    ImGui::BeginChild(mFilename.c_str(), mChildSize, ImGuiChildFlags_None, ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysUseWindowPadding);

    ImGui::Image(mImageID, mImageSize);

    InteractionWithItems(mCurrPathArray[i]);

    DisplayText(mCurrPathArray[i], mFilename, mImageSize);

    ImGui::EndChild();
}
