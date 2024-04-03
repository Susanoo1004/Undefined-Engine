#include "world/components/dir_light.h"

#include "resources/resource_manager.h"
#include "resources/shader.h"

DirLight::DirLight()
{
}

DirLight::DirLight(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular)
	: Light(ambient, diffuse, specular)
{
	mNbrOfDirLight++;
	mDirLightsArray.push_back(this);
}

DirLight::~DirLight()
{
}

void DirLight::Update()
{
   
}

int DirLight::GetNbrOfDirLight() const
{
	return mNbrOfDirLight;
}
