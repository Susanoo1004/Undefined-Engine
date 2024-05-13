#include "wrapper/physics_system.h"

#include <cstdarg>
#include <toolbox/Vector3.h>
#include <toolbox/Quaternion.h>

void PhysicsSystem::Init()
{
	JPH::RegisterDefaultAllocator();

	JPH::Trace = TraceImplentation;
	// JPH::JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;);

	JPH::Factory::sInstance = new JPH::Factory();

	JPH::RegisterTypes();

	temp_allocator = new JPH::TempAllocatorImpl(10 * 1024 * 1024);
	job_system = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);
	physics_system = new JPH::PhysicsSystem();

	physics_system->Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, broad_phase_layer_interface, object_vs_broadphase_layer_filter, object_vs_object_layer_filter);

	physics_system->SetBodyActivationListener(&body_activation_listener);
	physics_system->SetContactListener(&contact_listener);

	body_interface = &physics_system->GetBodyInterface();

	// ADD Floor

	// Create the settings for the collision volume (the shape)
	JPH::BoxShapeSettings floor_shape_settings(JPH::Vec3(100.0f, 1.0f, 100.0f));
	floor_shape_settings.SetEmbedded();

	// Create the shape
	JPH::ShapeSettings::ShapeResult floor_shape_result = floor_shape_settings.Create();
	JPH::ShapeRefC floor_shape = floor_shape_result.Get();

	JPH::BodyCreationSettings floor_settings(floor_shape, JPH::RVec3(0.0, -1.0, 0.0), JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING);

	floor = body_interface->CreateBody(floor_settings);

	// Add it to the world
	body_interface->AddBody(floor->GetID(), JPH::EActivation::DontActivate);


	// ADD dynamic body
	
	// Now create a dynamic body to bounce on the floor
	// Note that this uses the shorthand version of creating and adding a body to the world
	JPH::BodyCreationSettings sphere_settings(new JPH::SphereShape(0.5f), JPH::RVec3(0.0, 2.0, 0.0), JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, Layers::MOVING);
	sphere_id = body_interface->CreateAndAddBody(sphere_settings, JPH::EActivation::Activate);

	// Now you can interact with the dynamic body, in this case we're going to give it a velocity.
	// (note that if we had used CreateBody then we could have set the velocity straight on the body before adding it to the physics system)
	body_interface->SetLinearVelocity(sphere_id, JPH::Vec3(0.0f, -5.0f, 0.0f));
}

void PhysicsSystem::Update()
{
	physics_system->Update(1.f/60.f , 1, temp_allocator, job_system);
}

void PhysicsSystem::Terminate()
{
	// Remove the sphere from the physics system. Note that the sphere itself keeps all of its state and can be re-added at any time.
	body_interface->RemoveBody(sphere_id);

	// Destroy the sphere. After this the sphere ID is no longer valid.
	body_interface->DestroyBody(sphere_id);

	// Remove and destroy the floor
	body_interface->RemoveBody(floor->GetID());
	body_interface->DestroyBody(floor->GetID());

	// Unregisters all types with the factory and cleans up the default material
	JPH::UnregisterTypes();

	// Destroy the factory
	delete JPH::Factory::sInstance;
	JPH::Factory::sInstance = nullptr;
}

void PhysicsSystem::TraceImplentation(const char* inFMT, ...)
{
	va_list list;
	va_start(list, inFMT);
	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), inFMT, list);
	va_end(list);

	// Print to the TTY
	std::cout << buffer << std::endl;
}

JPH::Vec3Arg PhysicsSystem::ToJPH(const Vector3& in)
{
	return JPH::RVec3Arg(in.x, in.y, in.z);
}

JPH::QuatArg PhysicsSystem::ToJPH(const Quaternion& in)
{
	return JPH::QuatArg(in.x, in.y, in.z, in.w);
}

unsigned int PhysicsSystem::CreateBox(Vector3 pos, Quaternion rot, Vector3 scale)
{
	JPH::BodyCreationSettings settings(new JPH::BoxShape(ToJPH(scale)), ToJPH(pos), ToJPH(rot), JPH::EMotionType::Dynamic, Layers::MOVING);

	return body_interface->CreateAndAddBody(settings, JPH::EActivation::Activate).GetIndexAndSequenceNumber();
}

unsigned int PhysicsSystem::CreateCapsule(const Vector3& pos, const Quaternion& rot, float height, float radius)
{
	const JPH::CapsuleShapeSettings capsuleSettings(height, radius);
	const JPH::ShapeSettings::ShapeResult result = capsuleSettings.Create();

	if (!result.IsValid())
	{
		Logger::Error("[Physics] - Couldn't create the capsule shape");
		return JPH::BodyID::cInvalidBodyID;
	}

	JPH::BodyCreationSettings settings(result.Get(), ToJPH(pos), ToJPH(rot), JPH::EMotionType::Dynamic, Layers::MOVING);

	return body_interface->CreateAndAddBody(settings, JPH::EActivation::Activate).GetIndexAndSequenceNumber();
}

void PhysicsSystem::DestroyBody(unsigned int body_ID)
{
	body_interface->RemoveBody(JPH::BodyID(body_ID));
	body_interface->DestroyBody(JPH::BodyID(body_ID));
	ColliderMap.erase(ColliderMap.find(body_ID));
}

Collider* PhysicsSystem::GetColliderFromID(unsigned int body_ID)
{
	const auto&& it = ColliderMap.find(body_ID);

	if (it == ColliderMap.end())
		return nullptr;

	return it->second;
}
