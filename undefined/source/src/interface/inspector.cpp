#include "interface/inspector.h"

#include "interface/attributes.h"
#include "world/scene.h"
#include <imgui/imgui.h>
#include <ImGuizmo/ImGuizmo.h>
#include "interface/utils_reflection.h"

void Inspector::Init()
{
	mRenderer = ServiceLocator::Get<Renderer>();
}

void Inspector::ShowWindow(Scene* scene)
{
	ImGui::Begin("Inspector");
	
	if (mRenderer->pixelData >= 0)
	{
		Object* obj = scene->Objects[mRenderer->pixelData];
		Reflection::ReflectionObj<Object>(obj);
	}

	ImGui::Text(ImGuizmo::IsOver() ? "Over gizmo" : "Not over");

	
	ImGui::End();
}