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
	mRenderer->GenerateVertexArray(1, &CubeVAO);
	mRenderer->GenerateBuffer(1, &CubeVBO);
	mRenderer->BindBuffers(CubeVAO, CubeVBO, 0);
	mRenderer->SetBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), &CubeVertices, GL_STATIC_DRAW);
	mRenderer->AttributePointers(0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	mRenderer->AttributePointers(1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	//faces = ResourceManager::LoadFolder("../undefined/resource_manager/skybox");
	CubemapTexture = Texture::LoadCubeMap(Faces);

	mRenderer->ActiveTexture(GL_TEXTURE0);
	mRenderer->BindTexture(CubemapTexture, GL_TEXTURE_CUBE_MAP);
	mRenderer->BindBuffers(0, 0, 0);
}

void Skybox::Update(Camera* cam)
{
	mRenderer->UseShader(mSkyboxShader->ID);

	for (int i = 0; i < Interface::EditorViewports.size(); i++)
	{
		View = Matrix4x4(Matrix3x3(cam->GetView())); // remove translation from the view matrix
		mRenderer->SetUniform(mSkyboxShader->ID, "view", View);
		mRenderer->SetUniform(mSkyboxShader->ID, "projection", cam->GetProjection());
	}

	mRenderer->UnUseShader();
}

void Skybox::Draw()
{
	// skybox cube
	mRenderer->UseShader(mSkyboxShader->ID);

	// Has to be put in Renderer
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	mRenderer->BindBuffers(CubeVAO, 0, 0);
	mRenderer->ActiveTexture(GL_TEXTURE0);
	mRenderer->Draw(GL_TRIANGLES, 0, 36);
	mRenderer->BindBuffers(0, 0, 0);

	// Same as above
	glDepthFunc(GL_LESS); // set depth function back to default

	mRenderer->UnUseShader();
}
