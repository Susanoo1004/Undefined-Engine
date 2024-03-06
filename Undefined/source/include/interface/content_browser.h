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

	//Function to center text for ImGui texts
	UNDEFINED_ENGINE static void TextCentered(std::string text);
	UNDEFINED_ENGINE static void SetImageValues(std::filesystem::path path);
	UNDEFINED_ENGINE static void ShowText(std::string filename);
	UNDEFINED_ENGINE static void InteractionWithItems(std::filesystem::path path, bool isBackFolder = false);
	UNDEFINED_ENGINE static void GoBackFolder(std::filesystem::path path);

	static inline std::filesystem::path mPath;
	static inline std::filesystem::path mCurrentPath;
	static inline std::filesystem::path mHoveredPath;
	static inline std::filesystem::path mSelectedPath;

	static inline std::string mBackFolder;

	UNDEFINED_ENGINE static inline bool mIsFolderOpen;
	UNDEFINED_ENGINE static inline bool mIsDirectory;
	UNDEFINED_ENGINE static inline bool mIsAnythingHovered;
	UNDEFINED_ENGINE static inline bool mIsAnythingSelected;
	UNDEFINED_ENGINE static inline bool mCanPop;

	UNDEFINED_ENGINE static inline unsigned int mClickCountOffset;

	static inline ImVec2 mImageSize;
	static inline ImTextureID mImageID;
};