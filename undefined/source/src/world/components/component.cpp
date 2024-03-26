#include "world/components/component.h"

#include "world/scene_manager/object.h"

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