#include "world/scene_manager/object.h"

void Object::Enable()
{
	for (std::shared_ptr<Component> comp : Components)
	{
		comp->OnEnable();
	}
	mIsEnable = true;
}

void Object::Disable()
{
	for (std::shared_ptr<Component> comp : Components)
	{
		comp->OnDisable();
	}
	mIsEnable = false;
}

const bool Object::IsEnable() const
{
	return mIsEnable;
}
