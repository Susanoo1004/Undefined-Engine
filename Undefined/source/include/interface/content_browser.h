#pragma once

#include "utils/flag.h"
#include <filesystem>

class ContentBrowser
{
	STATIC_CLASS(ContentBrowser)

public:
	UNDEFINED_ENGINE static void Init();
	UNDEFINED_ENGINE static void DisplayDirectory(const std::filesystem::path& path);
	UNDEFINED_ENGINE static void ShowDirectory(std::filesystem::path actualPath);
	UNDEFINED_ENGINE static void ShowWindow();
	
private:
	static inline std::filesystem::path mPath;
	static inline std::filesystem::path mActualPath;
};