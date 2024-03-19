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

Transform& Object::GetTransform()
{
	return mTransform;
}

const Transform& Object::GetTransform() const
{
	return mTransform;
}

void Object::Test()
{
	for (std::shared_ptr<Component> comp : Components)
	{
		comp->Object.Ptr;
	}
}
