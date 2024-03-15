#pragma once

#include <filesystem>
#include <imgui/imgui.h>

#include "utils/flag.h"

class ContentBrowser
{
	STATIC_CLASS(ContentBrowser)

public:
	//Update for the ContentBrowser
	UNDEFINED_ENGINE static void DisplayWindow();
	
private:
	//Recursive function that displays the left side of the content browser who shows us every directory and file in a specific path
	UNDEFINED_ENGINE static void DisplayDirectories(const std::filesystem::path& path);

	//Display the right side of the content browser who shows an image for a file/folder in a directory
	UNDEFINED_ENGINE static void DisplayActualDirectory(std::filesystem::path currentPath);

	//Center text for ImGui texts
	UNDEFINED_ENGINE static void TextCentered(std::string text);

	//Set the image for the file we want to load
	UNDEFINED_ENGINE static void SetImageValues(std::filesystem::path path, ImTextureID& imageID, ImVec2& imageSize);

	//Print the text depending of it's lenght
	UNDEFINED_ENGINE static void DisplayText(std::string filename, ImVec2& imageSize);

	//Handle every interaction a folder/file can have
	UNDEFINED_ENGINE static void InteractionWithItems(std::filesystem::path path, bool isBackFolder = false);

	//Folder that put us to the parent path of the actual path
	UNDEFINED_ENGINE static void GoBackFolder(std::filesystem::path path);

	//Load folders in a path and add them to an array
	UNDEFINED_ENGINE static void LoadFolders(std::filesystem::path path);

	//Load files in a path and add them to an array
	UNDEFINED_ENGINE static void LoadFiles(std::filesystem::path path);

	//Load files in a path and add them to an array
	UNDEFINED_ENGINE static void RenameItem();

	UNDEFINED_ENGINE static inline bool mIsFolderOpen = false;
	UNDEFINED_ENGINE static inline bool mIsDirectory = false;
	UNDEFINED_ENGINE static inline bool mIsAnythingHovered = false;
	UNDEFINED_ENGINE static inline bool mIsAnythingSelected = false;
	UNDEFINED_ENGINE static inline bool mCanPop = false;

	static inline std::filesystem::path mPath = std::filesystem::current_path();
	static inline std::filesystem::path mCurrentPath = mPath;
	static inline std::filesystem::path mHoveredPath = "";
	static inline std::filesystem::path mSelectedPath = "";
	static inline std::filesystem::path mRenamingPath = "";

	static inline std::string mBackFolder = "BackFolder";
	
	static inline std::vector<std::filesystem::directory_entry> mCurrPathArray;
};