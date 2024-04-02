#include "world/components/skybox.h"

#include <glad/glad.h>
#include <stb_image/stb_image.h>

#include "engine_debug/logger.h"
#include "service_locator.h"
#include "resources/texture.h"
#include "resources/resource_manager.h"

#include "interface/interface.h"

void Skybox::Setup()
{
	mSkyboxShader = ResourceManager::Get<Shader>("skybox_shader");

	mRenderer = ServiceLocator::Get<Renderer>();

	//Cube setup
	mRenderer->GenerateVertexArray(1, &cubeVAO);
	mRenderer->GenerateBuffer(1, &cubeVBO);
	mRenderer->BindBuffers(cubeVAO, cubeVBO, 0);
	mRenderer->SetBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	mRenderer->AttributePointers(0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	mRenderer->AttributePointers(1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	//faces = ResourceManager::LoadFolder("../undefined/resource_manager/skybox");
	cubemapTexture = Texture::LoadCubeMap(faces);

	mRenderer->ActiveTexture(GL_TEXTURE0);
	mRenderer->BindTexture(cubemapTexture, GL_TEXTURE_CUBE_MAP);

	mRenderer->UseShader(mSkyboxShader->ID);
	mRenderer->SetUniform(mSkyboxShader->ID, "skybox", 0);
	mRenderer->UnUseShader();
	mRenderer->BindBuffers(0, 0, 0);
}

void Skybox::Update()
{
	mRenderer->UseShader(mSkyboxShader->ID);

	for (int i = 0; i < Interface::EditorViewports.size(); i++)
	{
		view = Matrix4x4(Matrix3x3(Interface::EditorViewports[i]->ViewportCamera->GetView())); // remove translation from the view matrix
		mRenderer->SetUniform(mSkyboxShader->ID, "view", view);
		mRenderer->SetUniform(mSkyboxShader->ID, "projection", Interface::EditorViewports[i]->ViewportCamera->GetProjection());
	}

	mRenderer->UnUseShader();
}

void Skybox::Draw()
{
	// skybox cube
	mRenderer->UseShader(mSkyboxShader->ID);
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	mRenderer->BindBuffers(cubeVAO, 0, 0);
	mRenderer->ActiveTexture(GL_TEXTURE0);
	mRenderer->Draw(GL_TRIANGLES, 0, 36);
	mRenderer->BindBuffers(0, 0, 0);
	glDepthFunc(GL_LESS); // set depth function back to default

	mRenderer->UnUseShader();
}
