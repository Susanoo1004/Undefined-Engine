#include "interface/inspector.h"

#include <imgui/imgui.h>
#include <ImGuizmo/ImGuizmo.h>
#include "reflection/attributes.h"
#include "reflection/utils_reflection.h"
#include "world/scene_manager.h"
#include "reflection/runtime_classes.h"

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
		
        if (ImGui::Button("Add Component"))
            ImGui::OpenPopup("component_popup");
        ImGui::SameLine();
        //ImGui::TextUnformatted(selected_fish == -1 ? "<None>" : names[selected_fish]);
        if (ImGui::BeginPopup("component_popup"))
        {
            ImGui::SeparatorText("Lights");
            for (int i = 0; i < RuntimeClasses::TabSize(); i++)
                //if (ImGui::Selectable(typeid(RuntimeClasses::GetClass[i]).name()))
            ImGui::EndPopup();
        }
	}

	ImGui::ShowDemoWindow();
	ImGui::End();
}