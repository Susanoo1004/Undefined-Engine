#include "world/components/component.h"

#include "world/scene_manager/object.h"
/*
Object& Component::GetObject()
{
	return GameObject;
}

Transform& Component::GetTransform()
{
	return GameObject.GetTransform();
}
*/

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