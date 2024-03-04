#include "world/component/light.h"

Light::Light()
{
}

Light::Light(const Vector3& position, const Vector3& rotation, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular)
	: ambient(ambient), diffuse(diffuse), specular(specular), pos(position), rot(rotation)
{
}

Light::~Light()
{
}

void Light::SetLight()
{
}

void Light::Update()
{
}
