#include "interface/scene_graph.h"

#include <imgui/imgui.h>
#include <toolbox/calc.h>

#include "world/scene_manager.h"
#include "service_locator.h"

#include "wrapper/time.h"

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
    RightClickObject(Object::mRoot);

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
            if (object == SceneManager::ActualScene->Objects[i])
            {
                ServiceLocator::Get<Renderer>()->ObjectIndex = (int)i;
            }
        }
    }
    if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
    {
        // Time for the travel time of the camera when double clicking to an object 
        mCamTravelTime = 0.4f;
        mLerpCam = true;
        mBaseCamPos = Camera::CurrentCamera->Eye;
    }
    if (mLerpCam)
    {
        Camera::CurrentCamera->Eye = calc::Lerp(mBaseCamPos, object->GameTransform->Position - Camera::CurrentCamera->LookAt, 1 - mCamTravelTime);

        mCamTravelTime -= Time::DeltaTime;

        if (mCamTravelTime <= 0)
        {
            mLerpCam = false;
        }
    }
}


void SceneGraph::RightClickObject(Object* object)
{

    if (ImGui::BeginPopupContextWindow(std::to_string(object->mUUID).c_str(), ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_NoOpenOverExistingPopup) ||
        ImGui::BeginPopupContextItem(std::to_string(object->mUUID).c_str(), ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverExistingPopup))
    {
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
