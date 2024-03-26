#include "interface/editor_viewport.h"

#include <imgui/imgui.h>

#include "resources/resource_manager.h"

EditorViewport::EditorViewport(Framebuffer* framebuffer)
	: mFramebuffer(framebuffer)
{
	mShader = ResourceManager::Get<Shader>("viewportShader");
}

EditorViewport::~EditorViewport()
{
	delete mFramebuffer;
}

void EditorViewport::Init()
{
	ServiceLocator::Get<Renderer>()->CreateQuad(mVBO, mEBO, mVAO);
}

void EditorViewport::ShowWindow()
{
	ImGui::Begin("Editor");

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
	
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer->FBO_ID);
	glUseProgram(mShader->ID);
	glBindVertexArray(mVAO);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	ImGui::End();


}

unsigned int EditorViewport::GetFBO_ID()
{
	return mFramebuffer->FBO_ID;
}
