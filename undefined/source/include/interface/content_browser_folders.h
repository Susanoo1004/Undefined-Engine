#pragma once

#include "interface/content_browser.h"

class ContentBrowserFolders : public ContentBrowser
{
	STATIC_CLASS(ContentBrowserFolders)

public:
	static void Update();

private:
	/// <summary>
	/// Display the right side of the content browser who shows an image for a file/folder in a directory
	/// </summary>
	/// <param name="currentPath">: Path of the current directory</param>
	static void DisplayActualDirectory(const std::filesystem::path& currentPath);

	/// <summary>
	/// Folder that put us to the parent path of the actual path
	/// </summary>
	/// <param name="path">: Path the backFolder will be displayed in</param>
	static void GoBackFolder(const std::filesystem::path& path);

	/// <summary>
	/// Load all the folders in a path and adds them to an array
	/// </summary>
	/// <param name="path">: The path you want to load</param>
	static void LoadFolders(const std::filesystem::path& path);

	/// <summary>
	/// Load all the files in a path and adds them to an array
	/// </summary>
	/// <param name="path">: The path you want to load</param>
	static void LoadFiles(const std::filesystem::path& path);

	static void CheckForPushStyle(int i);

	static void CheckForPopStyle(int i);

	static void SetAll(int i);
	
	static void LoadAll(const std::filesystem::path& currentPath);
	
	static void Clear();

	static void DrawFolders(int i);

	static inline std::string filename;

	static inline std::filesystem::path filepath;

	static inline ImVec2 imageSize;
	static inline ImVec2 childSize;

	static inline ImTextureID imageID;
};