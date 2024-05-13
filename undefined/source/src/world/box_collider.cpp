#include "world/box_collider.h"

#include "wrapper/physics_system.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::BoxCollider(Vector3 pos, Quaternion rot, Vector3 scale)
{
	pBodyID = PhysicsSystem::CreateBox(pos, rot, scale);

	PhysicsSystem::ColliderMap.emplace(pBodyID, this);
}
