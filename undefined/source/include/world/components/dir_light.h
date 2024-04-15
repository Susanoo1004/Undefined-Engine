#pragma once

#include <vector>

#include "world/components/light.h"

class DirLight : public Light
{
public:
	DirLight();
	DirLight(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular);
	~DirLight();

	void Update() override;
	int GetNbrOfDirLight() const;

private:
	static inline int mNbrOfDirLight;
	static inline std::vector<DirLight*> mDirLightsArray;
};

REFL_AUTO(type(DirLight, bases<Light>)
);