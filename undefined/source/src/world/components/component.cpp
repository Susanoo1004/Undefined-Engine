#include "world/components/component.h"

#include "world/scene_manager/object.h"

Object& Component::GetObject()
{
	return *Object.Ptr;
}

Transform& Component::GetTransform()
{
	return Object.Ptr->GetTransform();
}

const Transform& Component::GetTransform() const
{
	return Object.Ptr->GetTransform();
}

void Component::Enable()
{
	mIsEnable = true;
}

void Component::Disable()
{
	mIsEnable = false;
}

const bool Component::IsEnable() const
{
	return mIsEnable;
}