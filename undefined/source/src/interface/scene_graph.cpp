#include "interface/scene_graph.h"

#include <imgui/imgui.h>
#include <toolbox/calc.h>
#include <algorithm>

#include "world/scene_manager.h"
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
    RightClickObject(Object::mRoot);
    for (Object* object : Object::mRoot->GetChildren())
    {
        DisplayObject(object);
    }

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::Dummy(ImGui::GetContentRegionAvail());
    ImGui::PopStyleVar();
    BeginDropOnObject(Object::mRoot);
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

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::Dummy(ImVec2(ImGui::GetItemRectMax().x, 6.f));
    ImGui::PopStyleVar();
    BeginDropOnObject(object, true);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    if (ImGui::TreeNodeEx(object->Name.c_str(), flags))
    {
        ImGui::PopStyleVar();
        NodeInteraction(object);

        //For every child we call the function to display their children
        for (Object* child : object->GetChildren())
        {
            DisplayObject(child);
        }
        ImGui::TreePop();
    }
    else
    {
        ImGui::PopStyleVar();
        NodeInteraction(object);
    }

}

void SceneGraph::NodeInteraction(Object* object)
{
    ClickSelectObject(object);
    RightClickObject(object);
    BeginDragObject(object);
    BeginDropOnObject(object);
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
        float t = 1;
        Camera::CurrentCamera->Eye = calc::Lerp(Camera::CurrentCamera->Eye, object->GameTransform->Position - Camera::CurrentCamera->LookAt, t);
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

void SceneGraph::BeginDragObject(Object* object)
{
    // Our buttons are both drag sources and drag targets here!
    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAutoExpirePayload))
    {
        // Set payload to carry the index of our item (could be anything)
        ImGui::SetDragDropPayload("DragObject", &object, sizeof(Object*));

        // Display preview (could be anything, e.g. when dragging an image we could decide to display
        // the filename and a small preview of the image, etc.)
        ImGui::Text("%s", object->Name.c_str());
        ImGui::EndDragDropSource();
    }
}

void SceneGraph::BeginDropOnObject(Object* object, bool setBefore)
{
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragObject"))
        {
            IM_ASSERT(payload->DataSize == sizeof(Object*));
            Object* payloadObject = *(Object**)payload->Data;

            if (setBefore)
            {
                unsigned int index = 0; // find object index
                for (Object* find : object->mParent->mChildren)
                {
                    if (find == object)
                    {
                        object->mParent->AtachChild(payloadObject, index);
                        break;
                    }
                    index++;
                }
            }
            else
            {
                payloadObject->SetParent(object);
            }
        }
        ImGui::EndDragDropTarget();
    }
}

void SceneGraph::Print(Object* object, const char* plus)
{
    for (Object* test : object->mChildren)
    {
        Logger::Debug("{} {} : {}", plus, test->Name, test->mUUID);
        Print(test, ((std::string)plus + "[ ]").c_str());
    }
}
