#include "world/scene_manager/object.h"



Object::Object(const std::string& name)
	: Name(name), mParent(nullptr)
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

const Object* Object::GetParent() const
{
	return mParent;
}

void Object::SetParent(Object* parent)
{
	if (parent)
	{
		mParent = parent;
		mParent->mChildren.emplace_back(this);
		mTransform.mParentTransform = &parent->mTransform;
	}
}

const std::list<Object*> Object::GetChildren() const
{
	return mChildren;
}

void Object::DetachChildren()
{
	for (auto it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		(*it)->mParent = nullptr;
	}
	mChildren.clear();
}

const Object* Object::GetChild(unsigned int index) const
{
	if (index > mChildren.size())
	{
		return nullptr;
	}
	auto it = mChildren.begin();
	std::advance(it, index);
	return *(it);
}

const Object* Object::GetChild(std::string name) const
{
	//for (size_t i = 0; i < Children.size(); i++)
	for (auto it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		if ((*it)->Name == name)
		{
			return (*it);
		}
	}
	return nullptr;
}

void Object::DetachChild(unsigned int index)
{
	if (index < mChildren.size())
	{
		return;
	}
	auto it = mChildren.begin();
	std::advance(it, index);
	(*it)->mParent = nullptr;
	(*it)->mTransform.mParentTransform = nullptr;
	mChildren.remove(*it);
}

void Object::DetachChild(std::string name)
{
	for (Object* child : mChildren)
	{
		if (child->Name == name)
		{
			child->mParent = nullptr;
			child->mTransform.mParentTransform = nullptr;
			mChildren.remove(child);
		}
	}
}

void Object::DetachChild(Object* child)
{
	if (!child)
	{
		Logger::Warning("DetachChild(Object* child) argument invalid, child does not exist");
		return;
	}

	child->mParent = nullptr;
	child->mTransform.mParentTransform = nullptr;
	mChildren.remove(child);
}
