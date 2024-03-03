#pragma once

#include "utils/flag.h"
#include <filesystem>

class ContentBrowser
{
	STATIC_CLASS(ContentBrowser)

public:
	UNDEFINED_ENGINE static void Init();

	//Recursive function that displays the left side of the content browser who shows us every directory and file in a specific path
	UNDEFINED_ENGINE static void DisplayDirectory(const std::filesystem::path& path);

	//Display the right side of the content browser who shows an image for a file/folder in a directory
	UNDEFINED_ENGINE static void ShowDirectory(std::filesystem::path actualPath);
	
	//Update for the ContentBrowser
	UNDEFINED_ENGINE static void ShowWindow();
	
private:
	//Function to center text for ImGui texts
	static void TextCentered(std::string text);

	static inline std::filesystem::path mPath;
	static inline std::filesystem::path mActualPath;
};