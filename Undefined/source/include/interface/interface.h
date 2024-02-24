#pragma once 

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "utils/flag.h"

class UNDEFINED_ENGINE Interface
{
public:
	Interface();
	~Interface();

	static void Init();
	static void Update();
};