#include "world/components/light.h"

#include "resources/resource_manager.h"

Light::Light()
{
	Ambient = BASE_AMBIENT;
	Diffuse = BASE_DIFFUSE;
	Specular = BASE_SPECULAR;

	mBaseShader = ResourceManager::Get<Shader>("base_shader");
}

Light::Light(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular)
	: Ambient(ambient), Diffuse(diffuse), Specular(specular)
{
	mBaseShader = ResourceManager::Get<Shader>("base_shader");
}

Light::~Light()
{
}

void Light::Update()
{
}
