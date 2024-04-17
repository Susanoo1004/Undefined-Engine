#include "world/gizmo.h"

#include "camera/camera.h"

#include "world/transform.h"

Gizmo::Gizmo()
{
	Io = &ImGui::GetIO();
	viewManipulateRight = Io->DisplaySize.x;
	viewManipulateTop = 0;
	gizmoWindowFlags = 0;

    CurrentGizmoMode = ImGuizmo::WORLD;
}

void Gizmo::DrawGizmos(Camera* camera, Transform* transform)
{
    Matrix4x4 matrix = (CurrentGizmoMode == ImGuizmo::WORLD) ? transform->WorldMatrix() : transform->LocalMatrix();
    Matrix4x4 view = camera->GetView();

    ImGuizmo::SetDrawlist();
    float windowWidth = (float)ImGui::GetWindowWidth();
    float windowHeight = (float)ImGui::GetWindowHeight();
    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
    viewManipulateRight = ImGui::GetWindowPos().x + windowWidth;
    viewManipulateTop = ImGui::GetWindowPos().y;
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    gizmoWindowFlags = ImGui::IsWindowHovered() && ImGui::IsMouseHoveringRect(window->InnerRect.Min, window->InnerRect.Max) ? ImGuiWindowFlags_NoMove : 0;

    ImGuizmo::Manipulate(&camera->GetView()[0].x, &camera->GetProjection()[0].x, CurrentGizmoOperation, CurrentGizmoMode, &matrix[0].x , NULL, NULL, NULL, NULL);

    ImGuizmo::ViewManipulate(&view[0].x, (transform->Position - camera->Eye).Norm(), ImVec2(viewManipulateRight - 128, viewManipulateTop), ImVec2(128, 128), 0x10101010);
    
    if (CurrentGizmoMode == ImGuizmo::WORLD)
    {
        transform->SetWorldMatrix(matrix);
    }
    else if (CurrentGizmoMode == ImGuizmo::LOCAL)
    {
        transform->SetLocalMatrix(matrix);
    }

    camera->SetView(view);
}

void Gizmo::ChangeGizmoOperation()
{
    if (ImGui::RadioButton("Translate", CurrentGizmoOperation == ImGuizmo::TRANSLATE))
        CurrentGizmoOperation = ImGuizmo::TRANSLATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Rotate", CurrentGizmoOperation == ImGuizmo::ROTATE))
        CurrentGizmoOperation = ImGuizmo::ROTATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Scale", CurrentGizmoOperation == ImGuizmo::SCALE))
        CurrentGizmoOperation = ImGuizmo::SCALE;
}
