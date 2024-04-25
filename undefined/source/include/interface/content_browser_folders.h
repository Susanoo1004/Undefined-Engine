#pragma once

#include "interface/content_browser.h"

class ContentBrowserFolders : public ContentBrowser
{
	STATIC_CLASS(ContentBrowserFolders)

public:
	/// <summary>
	/// Update for the content browser folder
	/// </summary>
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

	/// <summary>
	/// Check if we can Push Style
	/// </summary>
	/// <param name="i">index of the element we want to check</param>
	static void CheckForPushStyle(int i = 0);

	/// <summary>
	/// Check if we can Pop Style
	/// </summary>
	/// <param name="i">index of the element we want to check</param>
	static void CheckForPopStyle();

	/// <summary>
	/// Set all the variables we want to set
	/// </summary>
	/// <param name="i">index of the element we want to check</param>
	static void SetAll(int i);
	
	/// <summary>
	/// Load the go back folder and the array 
	/// </summary>
	/// <param name="currentPath">path of what we want to load</param>
	static void LoadAll(const std::filesystem::path& currentPath);
	
	/// <summary>
	/// Clear the elements 
	/// </summary>
	static void Clear();

	/// <summary>
	/// Draw every folders
	/// </summary>
	/// <param name="i">index of the folder we want to draw</param>
	static void DrawFolders(int i);

	static inline bool isBackFolder;

	static inline std::string mFilename;

	static inline std::filesystem::path mFilepath;

	static inline ImVec2 mImageSize;
	static inline ImVec2 mChildSize;

	static inline ImTextureID mImageID;
};