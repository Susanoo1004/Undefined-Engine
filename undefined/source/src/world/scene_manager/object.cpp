#include "world/scene_manager/object.h"



Object::Object(const std::string& name)
	:Name(name)
{
}

Object::~Object()
{
	for (Component* comp : Components)
	{
		delete comp;
	}
}

void Object::Enable()
{
	for (Component* comp : Components)
	{
		comp->OnEnable();
	}
	mIsEnable = true;
}

void Object::Disable()
{
	for (Component* comp : Components)
	{
		comp->OnDisable();
	}
	mIsEnable = false;
}

const bool Object::IsEnable() const
{
	return mIsEnable;
}
