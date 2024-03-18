#include "world/scene_manager/object.h"

#include "world/components/component.h"

void Object::Enable()
{
	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i]->OnEnable();
	}
	isEnable = true;
}

void Object::Disable()
{
	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i]->OnDisable();
	}
	isEnable = false;
}

const bool Object::IsEnable() const
{
	return isEnable;
}

const Transform* Object::GetTransform() const
{
	return mTransform;
}
