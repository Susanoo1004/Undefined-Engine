#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>

#include <toolbox/Quaternion.h>

#include "world/collider.h"

class CapsuleCollider : public Collider
{
public:
	CapsuleCollider();
	CapsuleCollider(const Vector3& pos, const Quaternion& rot, float height, float radius);
	virtual ~CapsuleCollider();

private:
	float mHeight;
	float mRadius;
};