#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>

#include "world/rigidbody.h"
#include "world/object.h"
#include "world/component.h"
#include "world/script.h"

#include "engine_debug/logger.h"

class ColliderContactListener : public JPH::ContactListener, public Component
{
public:
	// See: ContactListener
	virtual JPH::ValidateResult OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult& inCollisionResult) override;

	virtual void OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override;

	virtual void OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override;

	virtual void OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair) override;

public:
	static void CallOnColliderEnter();
	static void CallOnColliderStay();
	static void CallOnColliderExit();
	
private:
	static inline std::vector<std::pair<Script*, const JPH::Body&>> mOnCollisionEnterScripts;
	static inline std::vector<std::pair<Script*, const JPH::Body&>> mOnCollisionStayScripts;
	static inline std::vector<Script*> OnCollisionExitScripts;
};