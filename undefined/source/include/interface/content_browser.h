#pragma once

#include <filesystem>
#include <imgui/imgui.h>

#include "utils/flag.h"

/// <summary>
/// ContentBrowser Class 
/// </summary>
class ContentBrowser
{
	STATIC_CLASS(ContentBrowser)

public:
	/// <summary>
	/// Update
	/// </summary>
	UNDEFINED_ENGINE static void DisplayWindow();
	
private:
	/// <summary>
	/// Recursive function that displays the left side of the content browser who shows us every directory and file in a specific path
	/// </summary>
	/// <param name="path">: Path of the directory</param>
	static void DisplayDirectories(const std::filesystem::path& path);

	static void RightClickInteractions(const std::filesystem::path& path);

	static void SetupTreeNodeFlags(ImGuiTreeNodeFlags& flags, const std::filesystem::path& path);

	/// <summary>
	/// Display the right side of the content browser who shows an image for a file/folder in a directory
	/// </summary>
	/// <param name="currentPath">: Path of the current directory</param>
	static void DisplayActualDirectory(const std::filesystem::path& currentPath);

	/// <summary>
	/// Center text for ImGui texts
	/// </summary>
	/// <param name="text">: Text to center</param>
	static void TextCentered(const std::string& text);

	/// <summary>
	/// Set the image for the file we want to load
	/// </summary>
	/// <param name="path">: Path of the image you want to set</param>
	/// <param name="imageID">: Set the ID of the image on the one in parameter</param>
	/// <param name="imageSize">: Set the size of the image on the one in parameter</param>
	static void SetImageValues(const std::filesystem::path& path, ImTextureID& imageID, ImVec2& imageSize);

	/// <summary>
	/// Display text on the screen depending of it's length
	/// </summary>
	/// <param name="filepath">: Filepath of the text displayed to center it in case we are renaming a file </param>
	/// <param name="filename">: Get the string of the filename to get the size </param>
	/// <param name="imageSize">: Size of the image</param>
	static void DisplayText(const std::filesystem::path& filepath, const std::string& filename, ImVec2& imageSize);

	/// <summary>
	/// Handle every interaction a folder/file can have
	/// </summary>
	/// <param name="path">: Path that the user intracts with </param> 
	/// <param name="isBackFolder">: Boolean value to know if it is the backfolder (by default : false)</param>
	static void InteractionWithItems(const std::filesystem::path& path, bool isBackFolder = false);

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

	//Rename an item in the content browser

	/// <summary>
	/// Rename an item with a simple text
	/// </summary>
	static void RenameItem();

	/// <summary>
	/// Rename an item with a multiline text
	/// </summary>
	static void RenameItemMultiline();

	//Window that pop when we right click
	
	/// <summary>
	/// Window that is displayed when we right click on something
	/// </summary>
	/// <param name="path">: Path of the current item on which we right clicked </param>
	static void RightClickWindow(const std::filesystem::path& path);

	/// <summary>
	/// Is folder open bool
	/// </summary>
	static inline bool mIsFolderOpen = false;
	/// <summary>
	/// Is the path we are in a directory
	/// </summary>
	static inline bool mIsDirectory = false;
	/// <summary>
	/// Is anythingHovered
	/// </summary>
	static inline bool mIsAnythingHovered = false;
	/// <summary>
	/// Is anything selected 
	/// </summary>
	static inline bool mIsAnythingSelected = false;
	/// <summary>
	/// Can ImGui pop
	/// </summary>
	static inline bool mCanPop = false;

	/// <summary>
	/// Initial path
	/// </summary>
	static inline std::filesystem::path mPath = std::filesystem::current_path().append("assets");
	/// <summary>
	/// Current path we are in
	/// </summary>
	static inline std::filesystem::path mCurrentPath = mPath;
	/// <summary>
	/// Hovered path
	/// </summary>
	static inline std::filesystem::path mHoveredPath = "";
	/// <summary>
	/// Selected path
	/// </summary>
	static inline std::filesystem::path mSelectedPath = "";
	/// <summary>
	/// Renaming path
	/// </summary>
	static inline std::filesystem::path mRenamingPath = "";

	static inline std::string mRenamingName = "";

	/// <summary>
	/// Back folder name
	/// </summary>
	static inline std::string mBackFolder = "BackFolder";
	
	/// <summary>
	/// Array of the current element in a path
	/// </summary>
	static inline std::vector<std::filesystem::directory_entry> mCurrPathArray;
};