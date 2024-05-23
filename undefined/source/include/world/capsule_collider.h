#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>

#include <refl.hpp>

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

	friend struct refl_impl::metadata::type_info__ <CapsuleCollider>;
};

REFL_AUTO(type(CapsuleCollider, bases<Collider>),
	field(mHeight),
	field(mRadius)
);