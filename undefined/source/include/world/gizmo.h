#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include <ImGuizmo/ImGuizmo.h>

class Camera;
class Transform;

class Gizmo
{
public:
	Gizmo();
	void DrawGizmos(Camera* camera, Transform* transform);

	void ChangeGizmoOperation();

	ImGuiIO* Io;
	float viewManipulateRight ;
	float viewManipulateTop;
	static inline ImGuiWindowFlags gizmoWindowFlags;

	static inline ImGuizmo::OPERATION CurrentGizmoOperation;
	static inline ImGuizmo::MODE CurrentGizmoMode;
};