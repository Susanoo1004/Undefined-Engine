#pragma once

#include <toolbox/Vector3.h>

#include "world/components/component.h"
#include "utils/flag.h"


#define BASE_AMBIENT Vector3{ 0.4f, 0.4f, 0.4f }
#define BASE_DIFFUSE Vector3{ 0.8f, 0.8f, 0.8f }
#define BASE_SPECULAR Vector3{ 0.5f, 0.5f, 0.5f }

class Light
{
public:
	UNDEFINED_ENGINE Light();
	UNDEFINED_ENGINE Light(const Vector3& position, const Vector3& rotation, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular);
	UNDEFINED_ENGINE ~Light();

	// TODO:
	UNDEFINED_ENGINE virtual void Update();

	Vector3 Ambient;
	Vector3 Diffuse;
	Vector3 Specular;

	// TO CHANGE into transform or whatever
	Vector3 pos;
	Vector3 rot;
};