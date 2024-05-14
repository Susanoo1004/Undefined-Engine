#pragma once

#include "interface/content_browser.h"

class ContentBrowserHierarchy : public ContentBrowser
{
	STATIC_CLASS(ContentBrowserHierarchy)

public:
	static void Update();

private:
	/// <summary>
	/// Recursive function that displays the left side of the content browser who shows us every directory and file in a specific path
	/// </summary>
	/// <param name="path">: Path of the directory</param>
	static void DisplayDirectories(const std::filesystem::path& path);
	/// <summary>
	/// Setup the flags for the tree node
	/// </summary>
	/// <param name="flags">adds the flag in the one given</param>
	/// <param name="path">path we loop on to see if  there is any child in the folder (tree or leaf)</param>
	static void SetupTreeNodeFlags(ImGuiTreeNodeFlags& flags, const std::filesystem::path& path);
	/// <summary>
	/// Handle every interaction user can have with the right click on tree node
	/// </summary>
	/// <param name="path">path of the element we right clicked on</param>
	static void RightClickInteractions(const std::filesystem::path& path);

	static inline std::string mName;
};