#include "world/components/component.h"

const Object* Component::GetObject() const
{
	return mObject;
}

const Transform* Component::GetTransform() const
{
	return mTransform;
}

void Component::Enable()
{
	isEnable = true;
}

void Component::Disable()
{
	isEnable = false;
}

const bool Component::IsEnable() const
{
	return isEnable;
}
