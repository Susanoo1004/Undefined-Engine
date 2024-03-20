#include "interface/editor_viewport.h"

#include <imgui/imgui.h>

EditorViewport::EditorViewport(Framebuffer* framebuffer)
	: mFramebuffer(framebuffer)
{
}

EditorViewport::~EditorViewport()
{
	delete mFramebuffer;
}

void EditorViewport::ShowWindow()
{
	ImGui::Begin("Inspector");

	const float windowWidth = ImGui::GetContentRegionAvail().x;
	const float windowHeight = ImGui::GetContentRegionAvail().y;

	mFramebuffer->RescaleFramebuffer(windowWidth, windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	// we get the screen position of the window
	ImVec2 pos = ImGui::GetCursorScreenPos();

	ImGui::GetWindowDrawList()->AddImage(
		(void*)mFramebuffer->RenderedTextures[0]->GetID(),
		ImVec2(pos.x, pos.y),
		ImVec2(pos.x + mFramebuffer->Width, pos.y + mFramebuffer->Height),
		ImVec2(0, 1),
		ImVec2(1, 0)
	);

	ImGui::End();
}
