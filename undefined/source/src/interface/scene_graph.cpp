#include "interface/scene_graph.h"

#include <imgui/imgui.h>

#include "world/scene_manager/scene_manager.h"
#include "service_locator.h"

void SceneGraph::DisplayWindow()
{
    ImGui::ShowDemoWindow();

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
    RightClickObject(Object::mRoot);
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

        RightClickObject(object);
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
        RightClickObject(object);
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
                ServiceLocator::Get<Renderer>()->pixelData = i;
            }
        }
    }
}


void SceneGraph::RightClickObject(Object* object)
{
    if (ImGui::BeginPopupContextItem(std::to_string(object->mUUID).c_str()))
    {
        Logger::Debug("");
        Logger::Debug("{}", object->Name);
        Logger::Debug("{}", object->mUUID);

        Logger::Debug("{}", Object::mRoot->Name);
        Logger::Debug("{}", Object::mRoot->mUUID);

        if (ImGui::BeginMenu(object->mUUID == Object::mRoot->mUUID ? "Add Object" : "Add Child"))
        {
            if (ImGui::MenuItem("Empty"))
            {
                SceneManager::ActualScene->AddObject(object, "Empty");
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::BeginMenu("Basic Shape"))
            {
                if (ImGui::MenuItem("Cube"))
                {
                    SceneManager::ActualScene->AddObject(object, "Cube");
                    //Add Model and Collider
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Capsule"))
                {
                    SceneManager::ActualScene->AddObject(object, "Capsule");
                    //Add Model and Collider
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Sphere"))
                {
                    SceneManager::ActualScene->AddObject(object, "Sphere");
                    //Add Model and Collider
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Model With Collider"))
            {
                if (ImGui::MenuItem("Cube"))
                {
                    SceneManager::ActualScene->AddObject(object, "Cube");
                    //Add Model and Collider
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Capsule"))
                {
                    SceneManager::ActualScene->AddObject(object, "Capsule");
                    //Add Model and Collider
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Sphere"))
                {
                    SceneManager::ActualScene->AddObject(object, "Sphere");
                    //Add Model and Collider
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndMenu();
            }
            
            ImGui::EndMenu();
        }

        ImGui::EndPopup();
    }
}
