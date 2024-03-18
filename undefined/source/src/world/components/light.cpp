#include "world/components/light.h"


// TODO: Remove
#include "logger/logger.h"

Light::Light()
{
}

Light::Light(const Vector3& position, const Vector3& rotation, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular)
	: Ambient(ambient), Diffuse(diffuse), Specular(specular)
{
	/*
	GetTransform().Position = position;
	GetTransform().Rotation = rotation;
	*/
}

Light::~Light()
{
}

void Light::Update()
{
	Logger::Debug("light Update");
}
