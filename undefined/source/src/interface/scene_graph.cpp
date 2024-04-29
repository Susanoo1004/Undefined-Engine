#include "interface/scene_graph.h"

#include <imgui/imgui.h>
#include <toolbox/calc.h>
#include <set>
#include <algorithm>

#include "world/scene_manager.h"
#include "service_locator.h"

static inline std::set<ImGuiID> openNextFrame;

void SceneGraph::DisplayWindow()
{
    ImGui::ShowDemoWindow();

    if (!SceneManager::ActualScene)
    {
        return;
    }

    ImGui::Begin("Hierarchy");
    if (ImGui::CollapsingHeader(SceneManager::ActualScene->Name.c_str(),
        ImGuiTreeNodeFlags_SpanAvailWidth |
        ImGuiTreeNodeFlags_FramePadding |
        ImGuiTreeNodeFlags_Leaf))

    DisplayActualScene();

    ImGui::End();
}

void SceneGraph::DisplayActualScene()
{
    RightClickObject(Object::mRoot);
    unsigned int labelID = 0;
    for (Object* object : Object::mRoot->GetChildren())
    {
        DisplayObject(object, labelID);
        labelID++;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::Dummy(ImGui::GetContentRegionAvail());
    ImGui::PopStyleVar();
    BeginDropOnObject(Object::mRoot);
}

void SceneGraph::DisplayObject(Object* object, unsigned int labelID)
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
    if (openNextFrame.contains(ImGui::GetID(object->Name.c_str())))
    {
        openNextFrame.erase(ImGui::GetID(object->Name.c_str()));
        ImGui::SetNextItemOpen(true);
    }

    std::string displayName = object->Name.c_str();
    if (object == mRenamingObject)
    {
        displayName = "##Renaming";
    }
    else if (object->Name == "")
    {
        displayName = "##Empty";
    }
    displayName += "##" + std::to_string(labelID);
    Logger::Debug("{}", displayName);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    if (ImGui::TreeNodeEx(displayName.c_str(), flags))
    {
        ImGui::PopStyleVar();
        NodeInteraction(object);

        //For every child we call the function to display their children
        for (Object* child : object->GetChildren())
        {
            labelID++;
            DisplayObject(child, labelID);
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
    if (RightClickObject(object))
    {
        openNextFrame.insert(ImGui::GetItemID());
    }
    BeginDragObject(object);
    if (BeginDropOnObject(object))
    {
        openNextFrame.insert(ImGui::GetItemID());
    }
    RenameObject(object);
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


bool SceneGraph::RightClickObject(Object* object)
{
    if (ImGui::BeginPopupContextWindow(std::to_string(object->mUUID).c_str(), ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_NoOpenOverExistingPopup) ||
        ImGui::BeginPopupContextItem(std::to_string(object->mUUID).c_str(), ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverExistingPopup))
    {
        mSelectedObject = object;
        bool success = false;
        if (ImGui::BeginMenu(object->mUUID == Object::mRoot->mUUID ? "Add Object" : "Add Child"))
        {
            if (ImGui::MenuItem("Empty"))
            {
                Object* newObject = SceneManager::ActualScene->AddObject(object, "Empty");
                ClickSelectObject(newObject);
                Logger::Debug("");
                Print(Object::mRoot, "");
                ImGui::CloseCurrentPopup();
                success = true;
            }
            if (ImGui::BeginMenu("Basic Shape"))
            {
                if (ImGui::MenuItem("Cube"))
                {
                    Object* newObject = SceneManager::ActualScene->AddObject(object, "Cube");
                    //Add Model and Collider
                    ClickSelectObject(newObject);
                    ImGui::CloseCurrentPopup();
                    success = true;
                }
                if (ImGui::MenuItem("Capsule"))
                {
                    Object* newObject = SceneManager::ActualScene->AddObject(object, "Capsule");
                    //Add Model and Collider
                    ClickSelectObject(newObject);
                    ImGui::CloseCurrentPopup();
                    success = true;
                }
                if (ImGui::MenuItem("Sphere"))
                {
                    Object* newObject = SceneManager::ActualScene->AddObject(object, "Sphere");
                    //Add Model and Collider
                    ClickSelectObject(newObject);
                    ImGui::CloseCurrentPopup();
                    success = true;
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Model With Collider"))
            {
                if (ImGui::MenuItem("Cube"))
                {
                    Object* newObject = SceneManager::ActualScene->AddObject(object, "Cube");
                    //Add Model and Collider
                    ClickSelectObject(newObject);
                    ImGui::CloseCurrentPopup();
                    success = true;
                }
                if (ImGui::MenuItem("Capsule"))
                {
                    Object* newObject = SceneManager::ActualScene->AddObject(object, "Capsule");
                    //Add Model and Collider
                    ClickSelectObject(newObject);
                    ImGui::CloseCurrentPopup();
                    success = true;
                }
                if (ImGui::MenuItem("Sphere"))
                {
                    Object* newObject = SceneManager::ActualScene->AddObject(object, "Sphere");
                    //Add Model and Collider
                    ClickSelectObject(newObject);
                    ImGui::CloseCurrentPopup();
                    success = true;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if (object->mUUID != Object::mRoot->mUUID && ImGui::Button("Rename"))
        {
            mRenamingObject = object;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
        return success;
    }
    return false;
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

bool SceneGraph::BeginDropOnObject(Object* object, bool setBefore)
{
    bool success = false;
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
            success = true;
        }
        ImGui::EndDragDropTarget();
    }
    return success;
}

void SceneGraph::RenameObject(Object* object)
{
    if (mRenamingObject == object)
    {
        ImGui::SameLine();
        ImGuiInputTextFlags flags = ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll;

        char* newName = (char*)object->Name.c_str();

        ImGui::SetKeyboardFocusHere();
        ImGui::PushItemWidth(ImGui::CalcTextSize(newName).x + 5);
        if (ImGui::InputText("##label", (char*)newName, 256, flags))
        {
            object->Name = newName;
            mRenamingObject = nullptr;
        }
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
