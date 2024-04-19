#include "interface/scene_graph.h"

#include <imgui/imgui.h>

#include "world/scene_manager.h"
#include "service_locator.h"

void SceneGraph::DisplayWindow()
{
    if (!SceneManager::ActualScene)
    {
        return;
    }

    ImGui::Begin("Hierarchy");
        //SceneManager::ActualScene->Name.c_str()

    DisplayActualScene();

    ImGui::End();
}

void SceneGraph::DisplayActualScene()
{
    for (Object* object : Object::mRoot->GetChildren())
    {
        DisplayObject(object);
    }
}

void SceneGraph::DisplayObject(Object* object)
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnArrow;

    if (object->GetChildren().size() < 1)
    {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    if (mSelectedObject == object)
    {
        flags |= ImGuiTreeNodeFlags_Selected;
    }
    
    //ImGui::Checkbox("##UUID???", &object->mIsEnable); // TODO: add refl
    //ImGui::SameLine();
    if (ImGui::TreeNodeEx(object->Name.c_str(), flags))
    {
        ClickSelectObject(object);

        //For every child we call the function to display their children
        for (Object* child : object->GetChildren())
        {
            DisplayObject(child);
        }

        ImGui::TreePop();
    }
    else
    {
        ClickSelectObject(object);
    }
}

void SceneGraph::ClickSelectObject(Object* object)
{
    if (!ImGui::IsItemToggledOpen() && ImGui::IsItemClicked(ImGuiMouseButton_Left))
    {
        mSelectedObject = object;
        for (size_t i = 0; i < SceneManager::ActualScene->Objects.size(); i++) // temp TODO: find
        {
            if (object == SceneManager::ActualScene->Objects[i]) // temp TODO: change Objects to vector
            {
                ServiceLocator::Get<Renderer>()->PixelData = (int)i;
            }
        }
    }
}
