#include "interface/inspector.h"

#include <imgui/imgui.h>
#include <ImGuizmo/ImGuizmo.h>
#include "reflection/attributes.h"
#include "reflection/utils_reflection.h"
#include "world/scene_manager.h"

void Inspector::Init()
{
	mRenderer = ServiceLocator::Get<Renderer>();
}

void Inspector::ShowWindow()
{
	ImGui::Begin("Inspector");
	
	if (mRenderer->ObjectIndex >= 0)
	{
		Object* obj = SceneManager::ActualScene->Objects[mRenderer->ObjectIndex];
		Reflection::ReflectionObj<Object>(obj);
	}

	ImGui::End();
}