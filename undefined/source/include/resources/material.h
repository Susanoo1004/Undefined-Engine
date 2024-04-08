#pragma once

#include "resources/resource_manager.h"
#include "resources/texture.h"
#include "resources/shader.h"

class Material
{
public:
	Material(std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader = ResourceManager::Get<Shader>("base_shader"));
	~Material();

	std::shared_ptr<Texture> MatTex;
	std::shared_ptr<Shader> MatShader;
};