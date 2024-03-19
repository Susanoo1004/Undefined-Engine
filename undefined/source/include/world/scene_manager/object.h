#pragma once

#include <list>

#include "utils/flag.h"

#include "world/components/component.h"
#include "logger/logger.h"

template<class Comp>
concept ComponentType = std::is_base_of<Component, Comp>::value;

class Object
{
public:

	void Enable();
	void Disable();
	const bool IsEnable() const;

	Transform& GetTransform();
	const Transform& GetTransform() const;


	template <ComponentType Comp, typename... Args>
	std::shared_ptr<Comp> AddComponent(Args... args)
	{
		std::shared_ptr<Comp> comp = nullptr;
		for (std::shared_ptr<Component> findComp : Components)
		{
			if (typeid(std::shared_ptr<Comp>) == typeid(findComp))
			{
				comp = std::dynamic_pointer_cast<Comp>(findComp);
				break;
			}
		}

		if (comp)
		{
			Logger::Error("Component {} already exist in object {}", typeid(Comp).name(), name);
			
			// TODO: decide between return null or already existing comp
			//return comp;
			return nullptr;
		}
		comp = std::make_shared<Comp>(args...);

		

		Components.push_back(comp);
		
		return comp;
	}

	template <ComponentType Comp>
	std::shared_ptr<Comp> GetComponent()
	{
		for (std::shared_ptr<Component> findComp : Components)
		{
			if (std::shared_ptr<Comp> castComp = std::dynamic_pointer_cast<Comp>(findComp))
			{
				return castComp;
			}
		}

		return nullptr;
	}

	void Test();

	std::string name = "empty";

	std::list<std::shared_ptr<Component>> Components;

private:
	bool mIsEnable = true;

	Transform mTransform;

};