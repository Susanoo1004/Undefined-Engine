#pragma once

#include <filesystem>
#include <imgui/imgui.h>

#include "utils/flag.h"

class UNDEFINED_ENGINE ContentBrowser
{
	STATIC_CLASS(ContentBrowser)

public:
	static void Init();
	
	//Update for the ContentBrowser
	static void ShowWindow();
	
private:
	//Recursive function that displays the left side of the content browser who shows us every directory and file in a specific path
	static void DisplayDirectories(const std::filesystem::path& path);

	//Display the right side of the content browser who shows an image for a file/folder in a directory
	static void ShowActualDirectory(std::filesystem::path currentPath);

	//Function to center text for ImGui texts
	static void TextCentered(std::string text);
	static void SetImageValues(std::filesystem::path path);
	static void ShowText(std::string filename, float size);

	static inline std::filesystem::path mPath;
	static inline std::filesystem::path mCurrentPath;
	static inline std::filesystem::path mHoveredPath;
	static inline std::filesystem::path mSelectedPath;

	static inline bool isFolderOpen;
	static inline bool isDirectory;
	static inline bool isAnythingHovered;
	static inline bool isAnythingSelected;
	static inline bool canPop;

	static inline ImVec2 imageSize;
	static inline ImTextureID imageID;
};