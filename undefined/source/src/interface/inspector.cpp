#include "interface/inspector.h"

#include "interface/attributes.h"
#include <imgui/imgui.h>
#include <ImGuizmo/ImGuizmo.h>
#include "interface/utils_reflection.h"

void Inspector::Init()
{
	mRenderer = ServiceLocator::Get<Renderer>();
}

void Inspector::ShowWindow()
{
	ImGui::Begin("Inspector");
	
	if (mRenderer->PixelData >= 0)
	{
		Object* obj = SceneManager::ActualScene->Objects[mRenderer->PixelData];
		Reflection::ReflectionObj<Object>(obj);
	}

	ImGui::Text(ImGuizmo::IsOver() ? "Over gizmo" : "Not over");

	
	ImGui::End();
}