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
	mShader->Use();
	mShader->SetVec3("dirLights[0].direction", GameTransform->Position);
	mShader->SetVec3("dirLights[0].ambient", Ambient);
	mShader->SetVec3("dirLights[0].diffuse", Diffuse);
	mShader->SetVec3("dirLights[0].specular", Specular);
	mShader->UnUse();
}

int DirLight::GetNbrOfDirLight() const
{
	return mNbrOfDirLight;
}
