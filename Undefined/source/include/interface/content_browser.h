#pragma once

#include <filesystem>
#include <imgui/imgui.h>

#include "utils/flag.h"

class ContentBrowser
{
	STATIC_CLASS(ContentBrowser)

public:
	UNDEFINED_ENGINE static void Init();
	
	//Update for the ContentBrowser
	UNDEFINED_ENGINE static void ShowWindow();
	
private:
	//Recursive function that displays the left side of the content browser who shows us every directory and file in a specific path
	UNDEFINED_ENGINE static void DisplayDirectories(const std::filesystem::path& path);

	//Display the right side of the content browser who shows an image for a file/folder in a directory
	UNDEFINED_ENGINE static void ShowActualDirectory(std::filesystem::path currentPath);

	//Center text for ImGui texts
	UNDEFINED_ENGINE static void TextCentered(std::string text);

	//Set the image for the file we want to load
	UNDEFINED_ENGINE static void SetImageValues(std::filesystem::path path, ImTextureID& imageID, ImVec2& imageSize);

	//Print the text depending of it's lenght
	UNDEFINED_ENGINE static void ShowText(std::string filename, ImVec2& imageSize);

	//Handle every interaction a folder/file can have
	UNDEFINED_ENGINE static void InteractionWithItems(std::filesystem::path path, bool isBackFolder = false);

	//Folder that put us to the parent path of the actual path
	UNDEFINED_ENGINE static void GoBackFolder(std::filesystem::path path);

	//Load folders in a path and add them to an array
	UNDEFINED_ENGINE static void LoadFolders(std::filesystem::path path);

	//Load files in a path and add them to an array
	UNDEFINED_ENGINE static void LoadFiles(std::filesystem::path path);

	UNDEFINED_ENGINE static inline bool mIsFolderOpen;
	UNDEFINED_ENGINE static inline bool mIsDirectory;
	UNDEFINED_ENGINE static inline bool mIsAnythingHovered;
	UNDEFINED_ENGINE static inline bool mIsAnythingSelected;
	UNDEFINED_ENGINE static inline bool mCanPop;

	static inline std::filesystem::path mPath;
	static inline std::filesystem::path mCurrentPath;
	static inline std::filesystem::path mHoveredPath;
	static inline std::filesystem::path mSelectedPath;

	static inline std::string mBackFolder;
	
	static inline std::vector<std::filesystem::directory_entry> mCurrPathArray;
};