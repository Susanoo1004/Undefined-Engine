#include "world/components/component.h"

#include "world/scene_manager/object.h"

Object& Component::GetObject()
{
	return *mObject;
}

Transform& Component::GetTransform()
{
	return mObject->GetTransform();
}

const Transform& Component::GetTransform() const
{
	return mObject->GetTransform();
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
