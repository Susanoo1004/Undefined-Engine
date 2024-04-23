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

	static void SetupTreeNodeFlags(ImGuiTreeNodeFlags& flags, const std::filesystem::path& path);
	
	static void RightClickInteractions(const std::filesystem::path& path);
};