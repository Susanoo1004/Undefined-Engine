#include "interface/editor_viewport.h"

#include <imgui/imgui.h>

#include <toolbox/calc.h>

#include "utils/utils.h"

#include "resources/resource_manager.h"

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

	ViewportCamera->Width = windowWidth;
	ViewportCamera->Height = windowHeight;

	Matrix4x4 result;
	if (windowHeight <= 0)
	{
		result = Matrix4x4::Identity();
	}
	else
	{
		if (windowWidth != mFramebuffer->Width)
			Logger::Debug("change");
		result = Matrix4x4::ProjectionMatrix(calc::PI / 2.0f, windowWidth / windowHeight, 0.1f, 20.0f);
		ViewportCamera->SetPerspective(result);
	}

	mFramebuffer->RescaleFramebuffer((unsigned int)windowWidth, (unsigned int)windowHeight);

	// we get the screen position of the window
	ImVec2 screenPos = ImGui::GetCursorScreenPos();
	glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
	
	ImGui::GetWindowDrawList()->AddImage(
		Utils::IntToPointer<ImTextureID>(mFramebuffer->RenderedTextures[0]->GetID()),
		ImVec2(screenPos.x, screenPos.y),
		ImVec2(screenPos.x + mFramebuffer->Width, screenPos.y + mFramebuffer->Height),
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
