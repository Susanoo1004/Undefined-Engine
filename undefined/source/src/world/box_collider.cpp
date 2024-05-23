#include "world/box_collider.h"

#include "wrapper/physics_system.h"

#include "service_locator.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::BoxCollider(const Vector3& pos, const Quaternion& rot, const Vector3& scale, bool is_static)
	: mSize(scale)
{
	BodyID = PhysicsSystem::CreateBox(pos, rot, scale, is_static);

	PhysicsSystem::ColliderMap.emplace(BodyID, this);
}

BoxCollider::~BoxCollider()
{
	if (!JPH::BodyID(BodyID).IsInvalid())
		PhysicsSystem::DestroyBody(BodyID);
}
