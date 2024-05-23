#include "interface/content_browser_folders.h"

void ContentBrowserFolders::Update()
{
    ImGui::SameLine();
    ImGui::BeginChild("Repertory", ImVec2(0, 0), ImGuiChildFlags_Border);

    DisplayActualDirectory(pCurrentPath);

    ImGui::EndChild();
}

void ContentBrowserFolders::DisplayActualDirectory(const std::filesystem::path& currentPath)
{
    LoadAll(currentPath);

    // For loop that goes through every file/folder in a path and displays them
    for (int i = 0; i < pCurrPathArray.size(); i++)
    {
        SetAll(i);

        CheckForPushStyle(i);

        DrawFolders(i);

        RightClickWindow(pCurrPathArray[i]);

        ImGui::SameLine();

        CheckForPopStyle();

        if (ImGui::GetCursorPosX() >= ImGui::GetContentRegionAvail().x * 2)
        {
            //Create a dummy if we can't create another child for a file/folder so it creates an empty space and go to a new line
            ImGui::Dummy(ImVec2(0, 0));
        }
    }

    if (!pSelectedPath.empty() && ImGui::IsKeyPressed(ImGuiKey_F2))
    {
        pRenamingPath = pSelectedPath;
    }

    Clear();
}

void ContentBrowserFolders::GoBackFolder(const std::filesystem::path& path)
{
    mIsBackFolder = true;
    pIsAnythingHovered = false;
    pIsDirectory = true;

    CheckForPushStyle();

    ImGui::SameLine();

    if (path != pPath)
    {
        mImageID = Utils::IntToPointer<ImTextureID>(ResourceManager::Get<Texture>("imgui/folder.png")->GetID());
        ImGui::Image(mImageID, ImVec2(80, 80));

        InteractionWithItems(pBackFolder, true);

        TextCentered("../");

        ImGui::EndChild();

        CheckForPopStyle();
    }
    ImGui::SameLine();

    mIsBackFolder = false;
}

void ContentBrowserFolders::LoadFolders(const std::filesystem::path& path)
{
    // For loop that goes through every file/folder in a path and displays them
    for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_directory())
        {
            pCurrPathArray.push_back(entry);
        }
    }
}

void ContentBrowserFolders::LoadFiles(const std::filesystem::path& path)
{
    for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(path))
    {
        if (!entry.is_directory())
        {
            pCurrPathArray.push_back(entry);
        }
    }
}

void ContentBrowserFolders::CheckForPushStyle(int i)
{
    if (mIsBackFolder)
    {
        if (pSelectedPath == pBackFolder)
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.7f, 0.7f, 0.7f, 0.7f));
            pCanPop = true;
        }
        else if (pHoveredPath == pBackFolder)
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));
            pCanPop = true;
        }

        return;
    }

    else
    {
        if (pSelectedPath == pCurrPathArray[i].path())
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.7f, 0.7f, 0.7f, 0.7f));
            pCanPop = true;
        }

        //If the mHoveredPath is the same as the path we're in we change it's style color
        else if (pHoveredPath == pCurrPathArray[i].path())
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));
            pCanPop = true;
        }

        return;
    }
}

void ContentBrowserFolders::CheckForPopStyle()
{
    if (pCanPop)
    {
        ImGui::PopStyleColor();
        pCanPop = false;
    }
}

void ContentBrowserFolders::SetAll(int i)
{
    pIsDirectory = pCurrPathArray[i].is_directory();

    mFilename = pCurrPathArray[i].path().filename().string();
    mFilepath = pCurrPathArray[i].path();

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
    if (!pIsAnythingHovered)
    {
        pHoveredPath = "";
    }
    else
    {
        pIsAnythingHovered = false;
    }

    pCurrPathArray.resize(0);
    pCurrPathArray.shrink_to_fit();
}

void ContentBrowserFolders::DrawFolders(int i)
{
    ImGui::BeginChild(mFilename.c_str(), mChildSize, ImGuiChildFlags_None, ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysUseWindowPadding);

    ImGui::Image(mImageID, mImageSize);

    InteractionWithItems(pCurrPathArray[i]);

    DisplayText(pCurrPathArray[i], mFilename, mImageSize);

    ImGui::EndChild();
}
