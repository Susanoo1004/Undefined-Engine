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
	ImGui::Begin((std::string("Editor ##") + std::to_string(mID)).c_str());

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
		if (ImGui::Button("Delete Editor Viewport"))
		{
			Interface::DeleteEditorViewport(mID);
			ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
			ImGui::End();
			return;
		}
		ImGui::EndPopup();
	}

	mWidth = ImGui::GetContentRegionAvail().x;
	mHeight = ImGui::GetContentRegionAvail().y;

	ViewportCamera->Width = mWidth;
	ViewportCamera->Height = mHeight;

	// we get the screen position of the window
	ImVec2 screenPos = ImGui::GetCursorScreenPos();
	
	ImGui::GetWindowDrawList()->AddImage(
		Utils::IntToPointer<ImTextureID>(mFramebuffer->RenderedTextures[0]->GetID()),
		ImVec2(screenPos.x, screenPos.y),
		ImVec2(screenPos.x + mWidth, screenPos.y + mHeight),
		ImVec2(0, 1),
		ImVec2(1, 0)
	);
	
	ImGui::End();
}

unsigned int EditorViewport::GetFBO_ID() const
{
	return mFramebuffer->FBO_ID;
}

int EditorViewport::GetEditorID() const
{
	return mID;
}

void EditorViewport::RescaleViewport()
{
	if (mWidth <= 0 || mHeight <= 0)
	{
		return;
	}

	Matrix4x4 result;
	if (mHeight <= 0)
	{
		result = Matrix4x4::Identity();
	}
	else
	{
		float aspect = mWidth / mHeight;
		if (aspect < 1.0f)
			aspect = mHeight / mWidth;

		result = Matrix4x4::ProjectionMatrix(calc::PI / 2.0f, aspect, 0.1f, 20.0f);
		ViewportCamera->SetPerspective(result);
	}

	mFramebuffer->RescaleFramebuffer((unsigned int)mWidth, (unsigned int)mHeight);

	// TODO add to Renderer
	glViewport(0, 0, (GLsizei)mWidth, (GLsizei)mHeight);
}
