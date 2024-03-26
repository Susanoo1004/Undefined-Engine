#include "world/components/skybox.h"

#include <glad/glad.h>
#include <stb_image/stb_image.h>

#include "engine_debug/logger.h"
#include "service_locator.h"
#include "resources/texture.h"
#include "resources/resource_manager.h"

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

	mSkyboxShader->SetInt("skybox", 0);
}

void Skybox::Update()
{
	mSkyboxShader->Use();

	Camera* camera = ServiceLocator::Get<Window>()->GetCamera();
	view = Matrix4x4(Matrix3x3(camera->GetView())); // remove translation from the view matrix

	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content

	mSkyboxShader->SetMat4("view", view);
	mSkyboxShader->SetMat4("projection", camera->GetProjection());

	// skybox cube
	mRenderer->BindBuffers(cubeVAO, 0, 0);
	mRenderer->ActiveTexture(GL_TEXTURE0);
	mRenderer->BindTexture(cubemapTexture, GL_TEXTURE_CUBE_MAP);
	mRenderer->Draw(GL_TRIANGLES, 0, 36);
	mRenderer->BindBuffers(0, 0, 0);

	glDepthFunc(GL_LESS); // set depth function back to default

	mSkyboxShader->UnUse();
}
