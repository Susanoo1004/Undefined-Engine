#include "interface/inspector.h"

#include <imgui/imgui.h>

#include "reflection/attributes.h"
#include "world/scene_manager.h"
#include "reflection/utils_reflection.h"

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
	
	ImGui::End();
}