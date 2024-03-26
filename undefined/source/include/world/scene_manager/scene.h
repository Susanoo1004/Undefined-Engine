#pragma once

#include "world/scene_manager/object.h"
#include "utils/flag.h"

class Scene
{
public:

	UNDEFINED_ENGINE void Start();
	UNDEFINED_ENGINE void FixedUpdate();
	UNDEFINED_ENGINE void Update();
	UNDEFINED_ENGINE void LateUpdate();

	template <typename... Args>
	Object* AddObject(Args... args)
	{
		Object* obj = new Object(args...);

		Objects.push_back(obj);

		return obj;
	}

	std::vector<Object*> Objects;
};