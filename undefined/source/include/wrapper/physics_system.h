#pragma once

#include <thread>
#include <unordered_map>

#include <Jolt/Jolt.h>

#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

#include "engine_debug/logger.h"

#include "world/collider_contact_listener.h"
#include "world/broad_phase_layer_interface.h"

#include "utils/flag.h"

#pragma region TOMOVE

#ifdef JPH_ENABLE_ASSERTS

// Callback for asserts, connect this to your own assert handler if you have one
static bool AssertFailedImpl(const char* inExpression, const char* inMessage, const char* inFile, unsigned int inLine)
{	
	// Print to the TTY
	// Logger::FatalError("{} : {} : ( {} ) {}", inFile, inLine, inExpression, (inMessage != nullptr ? inMessage : ""));
	std::cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr ? inMessage : "") << std::endl;
	// Breakpoint
	return true;
};

#endif // JPH_ENABLE_ASSERTSs

/// Class that determines if two object layers can collide
class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter
{
public:
	virtual bool ShouldCollide(JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2) const override
	{
		switch (inObject1)
		{
		case Layers::NON_MOVING:
			return inObject2 == Layers::MOVING; // Non moving only collides with moving
		case Layers::MOVING:
			return true; // Moving collides with everything
		default:
			JPH_ASSERT(false);
			return false;
		}
	}
};

/// Class that determines if an object layer can collide with a broadphase layer
class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter
{
public:
	virtual bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override
	{
		switch (inLayer1)
		{
		case Layers::NON_MOVING:
			return inLayer2 == BroadPhaseLayers::MOVING;
		case Layers::MOVING:
			return true;
		default:
			JPH_ASSERT(false);
			return false;
		}
	}
};

// An example activation listener
class MyBodyActivationListener : public JPH::BodyActivationListener
{
public:
	virtual void OnBodyActivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override
	{
		Logger::Info("A body got activated");
	}

	virtual void OnBodyDeactivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override
	{
		Logger::Info("A body went to sleep");
	}
};

#pragma endregion

class PhysicsSystem
{
	STATIC_CLASS(PhysicsSystem)
public:
	static void Init();

	static void Update();

	static void Terminate();

	static void TraceImplentation(const char* inFMT, ...);

	static JPH::Vec3Arg ToJPH(const Vector3& in);
	static JPH::QuatArg ToJPH(const Quaternion& in);

	static unsigned int CreateBox(Vector3 pos, Quaternion rot, Vector3 scale);
	static unsigned int CreateCapsule(const Vector3& pos, const Quaternion& rot, float height, float radius);

	static void DestroyBody(unsigned int body_ID);

	static Collider* GetColliderFromID(unsigned int bodyId);

	static inline JPH::TempAllocatorImpl* temp_allocator;

	// We need a job system that will execute physics jobs on multiple threads.
	static inline JPH::JobSystemThreadPool* job_system;

	static inline constexpr unsigned int cMaxBodies = 1024;

	static inline constexpr unsigned int cNumBodyMutexes = 0;

	static inline constexpr unsigned int cMaxBodyPairs = 1024;

	static inline constexpr unsigned int cMaxContactConstraints = 1024;

	static inline BroadPhaseLayerInterface broad_phase_layer_interface;

	static inline ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;

	static inline ObjectLayerPairFilterImpl object_vs_object_layer_filter;

	static inline JPH::PhysicsSystem* JoltPhysicsSystem;

	static inline MyBodyActivationListener body_activation_listener;
	static inline ColliderContactListener ContactListener;

	static inline JPH::BodyInterface* BodyInterface;

	static inline JPH::Body* floor = nullptr;
	static inline JPH::BodyID sphere_id;

	static inline std::unordered_map<unsigned int, Collider*> ColliderMap;

};

