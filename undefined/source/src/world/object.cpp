#include "world/object.h"

Object::Object()
	: Name("Default")
{
}

Object::Object(const std::string& name)
	: Name(name)
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
	if (mParent == mRoot)
	{
		return nullptr;
	}
	return mParent;
}

void Object::SetParent(Object* parent)
{
	if ((mParent && mParent == parent) || this == parent)
	{
		return;
	}

	if (mParent)
	{
		mParent->DetachChild(this);
	}

	if (parent)
	{
		Object* current = parent;
		while (current->mParent != mRoot && current->mParent != nullptr)
		{
			if (current->mParent == this)
			{
				return;
			}

			current = current->mParent;
		}

		mParent = parent;
		mParent->mChildren.emplace_back(this);
		mTransform.mParentTransform = &parent->mTransform;
	}
	else
	{
		mParent = mRoot;
		mParent->mChildren.emplace_back(this);
		mTransform.mParentTransform = nullptr;
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
		(*it)->mParent = mRoot;
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
	(*it)->mParent = mRoot;
	(*it)->mTransform.mParentTransform = nullptr;
	mChildren.remove(*it);
}

void Object::DetachChild(std::string name)
{
	for (Object* child : mChildren)
	{
		if (child->Name == name)
		{
			child->mParent = mRoot;
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

	child->mParent = mRoot;
	child->mTransform.mParentTransform = nullptr;
	mChildren.remove(child);
}

void Object::ChangeEnableStatus()
{
	if (mIsEnable)
	{
		Enable();
	}
	else
	{
		Disable();
	}
}
