#include "world/capsule_collider.h"

#include "wrapper/physics_system.h"

CapsuleCollider::CapsuleCollider()
{
}

CapsuleCollider::CapsuleCollider(const Vector3& pos, const Quaternion& rot, float height, float radius)
	: mHeight(height), mRadius(radius)
{
	BodyID = PhysicsSystem::CreateCapsule(pos, rot, height, radius);

	PhysicsSystem::ColliderMap.emplace(BodyID, this);
}

CapsuleCollider::~CapsuleCollider()
{
	if (!JPH::BodyID(BodyID).IsInvalid())
		PhysicsSystem::DestroyBody(BodyID);
}
