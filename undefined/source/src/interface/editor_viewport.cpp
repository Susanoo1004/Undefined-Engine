#include "interface/editor_viewport.h"

#include <imgui/imgui.h>

#include "utils/utils.h"

#include "resources/resource_manager.h"

EditorViewport::EditorViewport(Framebuffer* framebuffer)
	: mFramebuffer(framebuffer)
{
	mShader = ResourceManager::Get<Shader>("viewport_shader");
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
	auto viewportOffset = ImGui::GetCursorPos();

	//min and max size of the framebuffer and mouse pos
	ImVec2 minBound = ImGui::GetWindowPos();
	minBound.x += viewportOffset.x;
	minBound.y += viewportOffset.y;
	ImVec2 maxBound = { minBound.x + windowWidth, minBound.y + windowHeight };
	mViewportBounds[0] = { minBound.x, minBound.y };
	mViewportBounds[1] = { maxBound.x, maxBound.y };
	auto [mx, my] = ImGui::GetMousePos();
	mx -= mViewportBounds[0].x;
	my -= mViewportBounds[0].y;
	Vector2 viewportSize = mViewportBounds[1] - mViewportBounds[0];
	my = viewportSize.y - my;
	int mouseX = (int)mx;
	int mouseY = (int)my;

	mFramebuffer->RescaleFramebuffer((unsigned int)windowWidth, (unsigned int)windowHeight);
	glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);

	// we get the screen position of the window
	ImVec2 pos = ImGui::GetCursorScreenPos();
	
	ImGui::GetWindowDrawList()->AddImage(
		Utils::IntToPointer<ImTextureID>(mFramebuffer->RenderedTextures[0]->GetID()),
		ImVec2(pos.x, pos.y),
		ImVec2(pos.x + mFramebuffer->Width, pos.y + mFramebuffer->Height),
		ImVec2(0, 1),
		ImVec2(1, 0)
	);
	
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer->FBO_ID);
	glUseProgram(mShader->ID);
	glBindVertexArray(mVAO);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
	{
		int pixelData = ServiceLocator::Get<Renderer>()->ReadPixels(1, mouseX, mouseY);
		Logger::Debug("Pixel data = {}", pixelData);
	}

	glBindVertexArray(0);
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	ImGui::End();
}

unsigned int EditorViewport::GetFBO_ID()
{
	return mFramebuffer->FBO_ID;
}
