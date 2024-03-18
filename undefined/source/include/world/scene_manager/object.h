#pragma once

#include <set>

#include "utils/flag.h"

#include "world/components/component.h"

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
	Comp& AddComponent(Comp test, Args... args)
	{
		Components.insert(Comp(args));
	}

	template <ComponentType Comp>
	Comp& GetComponent()
	{
		return Components.find<Comp>();
	}


	std::set<Component> Components;

private:
	bool mIsEnable = true;

	Transform mTransform;

};