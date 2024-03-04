#pragma once

#include "world/component/light.h"

class DirLight : public Light
{
public:
	UNDEFINED_ENGINE DirLight();
	UNDEFINED_ENGINE DirLight(const Vector3& rotation, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular);
	UNDEFINED_ENGINE ~DirLight();

	void SetLight() override;
	void Update() override;

};