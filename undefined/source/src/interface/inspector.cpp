#include "interface/inspector.h"
#include "interface/attributes.h"
#include "world/scene_manager/scene.h"
#include <imgui/imgui.h>
#include "interface/utils_reflection.h"

void Inspector::Init()
{
	mRenderer = ServiceLocator::Get<Renderer>();
}

void Inspector::ShowWindow(Scene* scene)
{
	ImGui::Begin("Inspector");
	
	Object* obj = scene->Objects[mRenderer->pixelData];

	ReflectionObj<Object>(obj);
	
	ImGui::End();
}