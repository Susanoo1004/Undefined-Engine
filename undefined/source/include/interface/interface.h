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
	UNDEFINED_ENGINE static void CreateEditorViewport();
	UNDEFINED_ENGINE static void DeleteEditorViewport(int ID);

	static void Init();
	static void Update();
	static void Render();
	static void Delete();

	static inline std::vector<EditorViewport*> EditorViewports;

private:
	static void NewFrame();
	static void BeginDockSpace();
};