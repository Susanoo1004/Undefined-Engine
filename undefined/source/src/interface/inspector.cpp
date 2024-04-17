#include "interface/inspector.h"

#include "interface/attributes.h"
#include "world/scene.h"
#include <imgui/imgui.h>
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
	
	ImGui::End();
}