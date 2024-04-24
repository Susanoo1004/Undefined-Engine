#pragma once

#include <filesystem>
#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include "resources/resource_manager.h"
#include "resources/texture.h"

#include "utils/flag.h"
#include "utils/utils.h"

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
	static void DisplayWindow();
	
protected:
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
	static void SetImageValues(const std::filesystem::path& path, ImTextureID& mImageID, ImVec2& mImageSize);

	/// <summary>
	/// Display text on the screen depending of it's length
	/// </summary>
	/// <param name="filepath">: Filepath of the text displayed to center it in case we are renaming a file </param>
	/// <param name="filename">: Get the string of the filename to get the size </param>
	/// <param name="imageSize">: Size of the image</param>
	static void DisplayText(const std::filesystem::path& mFilepath, const std::string& mFilename, ImVec2& mImageSize);

	/// <summary>
	/// Handle every interaction a folder/file can have
	/// </summary>
	/// <param name="path">: Path that the user intracts with </param> 
	/// <param name="isBackFolder">: Boolean value to know if it is the backfolder (by default : false)</param>
	static void InteractionWithItems(const std::filesystem::path& path, bool isBackFolder = false);

	/// <summary>
	/// Rename an item with a simple text
	/// </summary>
	static void RenameItem();

	/// <summary>
	/// Rename an item with a multiline text
	/// </summary>
	static void RenameItemMultiline();

	/// <summary>
	/// Window that is displayed when we right click on something
	/// </summary>
	/// <param name="path">: Path of the current item on which we right clicked </param>
	static void RightClickWindow(const std::filesystem::path& path);

	/// <summary>
	/// Return true if we double click
	/// </summary>
	/// <returns></returns>
	static bool DoubleClick();

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

	static inline int clickCount;
};