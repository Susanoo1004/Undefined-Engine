#pragma once 

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <filesystem>
#include <vector>

#include "utils/flag.h"

class UNDEFINED_ENGINE Interface
{
	STATIC_CLASS(Interface)

public:
	static void Init();

	static void Update();
	static void NewFrame();
	static void BeginDockSpace();
	static void Render();

	static void Delete();
};