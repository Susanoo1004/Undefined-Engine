#include "world/component/dir_light.h"

#include "resources/resource_manager.h"
#include "resources/shader.h"

DirLight::DirLight()
{
}

DirLight::DirLight(const Vector3& rotation, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular)
	: Light(Vector3(0), rotation, ambient, diffuse, specular)
{
}

DirLight::~DirLight()
{
}

void DirLight::SetLight()
{
}

void DirLight::Update()
{
   
}
