#pragma once 

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <filesystem>
#include <vector>

#include "utils/flag.h"

#include "interface/editor_viewport.h"

class Interface
{
	STATIC_CLASS(Interface)

public:
	UNDEFINED_ENGINE static void Init();

	UNDEFINED_ENGINE static void Update();
	UNDEFINED_ENGINE static void NewFrame();
	UNDEFINED_ENGINE static void BeginDockSpace();
	UNDEFINED_ENGINE static void Render();

	static inline std::vector<EditorViewport> EditorViewports;

	UNDEFINED_ENGINE static void Delete();
};