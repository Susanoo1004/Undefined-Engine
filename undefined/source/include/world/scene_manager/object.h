#pragma once

#include <list>

#include "utils/flag.h"

#include "world/components/component.h"
#include "engine_debug/logger.h"
#include "interface/attributes.h"

template<class Comp>
concept ComponentType = std::is_base_of<Component, Comp>::value;

class Object
{
public:
	UNDEFINED_ENGINE Object();
	UNDEFINED_ENGINE Object(const std::string& name);
	UNDEFINED_ENGINE ~Object();

	UNDEFINED_ENGINE void Enable();
	UNDEFINED_ENGINE void Disable();
	UNDEFINED_ENGINE const bool IsEnable() const;

	template <ComponentType Comp, typename... Args>
	Comp* AddComponent(Args... args)
	{
		Comp* comp = nullptr;
		for (Component* findComp : Components)
		{
			if (typeid(Comp*) == typeid(findComp))
			{
				comp = (Comp*)findComp;
				break;
			}
		}

		if (comp)
		{
			Logger::Error("Component {} already exist in object {}", typeid(Comp).name(), Name);
			return nullptr;
		}
		comp = new Comp(args...);

		comp->GameObject = this;
		comp->GameTransform = GameTransform;

		Components.push_back(comp);
		
		return comp;
	}

	template <ComponentType Comp>
	Comp* GetComponent()
	{
		for (Component* findComp : Components)
		{
			if (Comp* castComp = (Comp*)findComp)
			{
				return castComp;
			}
		}

		return nullptr;
	}

	__declspec(property(get = GetTransform, put = SetTransform)) Transform* GameTransform;
	UNDEFINED_ENGINE Transform* GetTransform() { return &mTransform; };

	__declspec(property(get = GetParent, put = SetParent)) Object* Parent; // TODO: See if necessary and useful
	UNDEFINED_ENGINE const Object* GetParent() const;
	UNDEFINED_ENGINE void SetParent(Object* parent);

	UNDEFINED_ENGINE const std::list<Object*> GetChildren() const;
	UNDEFINED_ENGINE void DetachChildren();
	UNDEFINED_ENGINE const Object* GetChild(unsigned int index) const;
	UNDEFINED_ENGINE const Object* GetChild(std::string name) const;
	UNDEFINED_ENGINE void DetachChild(unsigned int index);
	UNDEFINED_ENGINE void DetachChild(std::string name);
	UNDEFINED_ENGINE void DetachChild(Object* child);

	std::string Name = "empty";

	std::list<Component*> Components;

private:
	void SetTransform(Transform newTransform) { mTransform = newTransform; };
	void SetTransform(Transform* newTransform) { mTransform = *newTransform; };

	Transform mTransform;
	Object* mParent;
	std::list<Object*> mChildren;

	bool mIsEnable = true;

	friend struct refl_impl::metadata::type_info__ <Object>;

private:

	friend class SceneManager;
	friend class SceneGraph;
	static inline Object* mRoot;
};

REFL_AUTO(type(Object),
	field(mIsEnable, DontDisplayName()),
	field(Name, SameLine()),
	field(mTransform)
)