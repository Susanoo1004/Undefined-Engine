#include "interface/editor_viewport.h"

#include <imgui/imgui.h>

#include <toolbox/calc.h>

#include <vector>

#include "utils/utils.h"

#include "resources/resource_manager.h"

#include "resources/texture.h"

#include "interface/interface.h"

EditorViewport::EditorViewport(Framebuffer* framebuffer, Camera* camera)
	: mFramebuffer(framebuffer), ViewportCamera(camera), mShader(ResourceManager::Get<Shader>("viewport_shader"))
{
	mEditorNumber++;
	mID = mEditorNumber;
}

EditorViewport::~EditorViewport()
{
	mEditorNumber--;
	delete mFramebuffer;
	delete ViewportCamera;
}

void EditorViewport::Init()
{
	ServiceLocator::Get<Renderer>()->CreateQuad(mVBO, mEBO, mVAO);
}

void EditorViewport::ShowWindow()
{
	ImGui::Begin(((std::string)"Editor " + std::to_string(mID)).c_str());

	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows))
	{
		Camera::CurrentCamera = ViewportCamera;
	}

	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::Button("Create Editor Viewport"))
		{
			Interface::CreateEditorViewport();
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

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

	ViewportCamera->Width = windowWidth;
	ViewportCamera->Height = windowHeight;

	Matrix4x4 result;
	if (windowHeight <= 0)
	{
		result = Matrix4x4::Identity();
	}

	else
	{
		result = Matrix4x4::ProjectionMatrix(calc::PI / 2.0f, windowWidth / windowHeight, 0.1f, 20.0f);
	}
	ViewportCamera->SetPerspective(result);

	mFramebuffer->RescaleFramebuffer((unsigned int)windowWidth, (unsigned int)windowHeight);
	//glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);

	// we get the screen position of the window
	ImVec2 pos = ImGui::GetCursorScreenPos();

	if (ff)
	{
		ImGui::GetWindowDrawList()->AddImage(
			Utils::IntToPointer<ImTextureID>(mFramebuffer->RenderedTextures[1]->GetID()),
			ImVec2(pos.x, pos.y),
			ImVec2(pos.x + windowWidth, pos.y + windowHeight),
			ImVec2(0, 1),
			ImVec2(1, 0)
		);
	}

	else
	{
		ImGui::GetWindowDrawList()->AddImage(
			Utils::IntToPointer<ImTextureID>(mFramebuffer->RenderedTextures[0]->GetID()),
			ImVec2(pos.x, pos.y),
			ImVec2(pos.x + windowWidth, pos.y + windowHeight),
			ImVec2(0, 1),
			ImVec2(1, 0)
		);
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer->FBO_ID);
	glUseProgram(mShader->ID);
	glBindVertexArray(mVAO);
	
	if (ImGui::IsKeyDown(ImGuiKey_V))
	{
		ff = true;
	}
	else
	{
		ff = false;
	}

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
	{
		mFramebuffer->AttachTexture(1, GL_RED, mFramebuffer->RenderedTextures[1]->GetID());
		int pixelData = ServiceLocator::Get<Renderer>()->ReadPixels(1, mouseX, mouseY);
		Logger::Debug("Pixel data = {}", pixelData);

		//mFramebuffer->AttachTexture(0, GL_RGB, mFramebuffer->RenderedTextures[0]->GetID());
		//glUseProgram(mShader->ID);
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
