#pragma once

#include <list>

#include "utils/flag.h"

#include "world/components/component.h"
#include "engine_debug/logger.h"

template<class Comp>
concept ComponentType = std::is_base_of<Component, Comp>::value;

class Object
{
public:
	Object(const std::string& name);
	~Object();

	void Enable();
	void Disable();
	const bool IsEnable() const;

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

	std::string Name = "empty";

	Transform* GameTransform = new Transform;

	std::list<Component*> Components;

private:
	bool mIsEnable = true;
};