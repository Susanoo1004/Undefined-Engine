#pragma once 

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <filesystem>

#include "utils/flag.h"

class UNDEFINED_ENGINE Interface
{
public:
	Interface();
	~Interface();

	static void Init();

	static void Update();
	static void NewFrame();
	static void BeginDockSpace();
	static void Render();

	static void ContentBrowserDirectory(const std::filesystem::path& path);

	static void ContentBrowser();
	static void Inspector();
};