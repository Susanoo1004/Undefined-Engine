#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>

#include <toolbox/Quaternion.h>

#include "world/collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider();
	BoxCollider(Vector3 pos, Quaternion rot, Vector3 scale);

private:
};