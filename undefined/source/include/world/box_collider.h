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
	BoxCollider(const Vector3& pos, const Quaternion& rot, const Vector3& scale, bool is_static = false);
	virtual ~BoxCollider();

private:
	Vector3 mSize;
};