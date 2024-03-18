#pragma once
#include <toolbox/Vector3.h>

#include "world/components/component.h"

class Transform : Component
{
public:

	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scale;

private:

};