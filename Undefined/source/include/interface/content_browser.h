#pragma once

#include "utils/flag.h"
#include <filesystem>

class UNDEFINED_ENGINE ContentBrowser
{
	STATIC_CLASS(ContentBrowser)

public:
	static void Init();
	static void DisplayDirectory(const std::filesystem::path& path);
	static void ShowDirectory();
	static void ShowWindow();
	
private:
	static inline std::filesystem::path mPath;
};