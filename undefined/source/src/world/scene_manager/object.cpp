#include "world/scene_manager/object.h"

void Object::Enable()
{
	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i]->OnEnable();
	}
	mIsEnable = true;
}

void Object::Disable()
{
	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i]->OnDisable();
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
