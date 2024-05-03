#include "world/collider_contact_listener.h"

JPH::ValidateResult ColliderContactListener::OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult& inCollisionResult)
{
	Logger::Info("Contact validate callback");

	// Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
	return JPH::ValidateResult::AcceptAllContactsForThisBodyPair;
}

void ColliderContactListener::OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
{
	Logger::Info("A contact was added");
	Script* script = GameObject->GetComponent<Script>();

	if (script)
	{	
		mOnCollisionEnterScripts.push_back(std::make_pair(script, inBody2));
	}
}
void ColliderContactListener::OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
{
	Logger::Info("A contact was persisted");
	Script* script = GameObject->GetComponent<Script>();

	if (script)
	{
		std::pair<Script*, const JPH::Body&> p = std::make_pair(script, inBody2);

		mOnCollisionStayScripts.push_back(p);
	}
}

void ColliderContactListener::OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair)
{
	Logger::Info("A contact was removed");
	Script* script = GameObject->GetComponent<Script>();

	if (script)
	{
		OnCollisionExitScripts.push_back(script);
	}
}

void ColliderContactListener::CallOnColliderEnter()
{
	for (std::pair<Script*, const JPH::Body&> p : mOnCollisionEnterScripts)
	{
		p.first->OnCollisionEnter(p.second);
	}
}

void ColliderContactListener::CallOnColliderStay()
{
	for (std::pair<Script*, const JPH::Body&> p : mOnCollisionStayScripts)
	{
		p.first->OnCollisionStay(p.second);
	}
}

void ColliderContactListener::CallOnColliderExit()
{
	for (Script* s : OnCollisionExitScripts)
	{
		s->OnCollisionExit();
	}
}
