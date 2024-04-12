#pragma once

#include "world/scene_manager/object.h"
#include "utils/flag.h"

class Scene
{
public:
	UNDEFINED_ENGINE ~Scene();

	UNDEFINED_ENGINE void Start();
	UNDEFINED_ENGINE void FixedUpdate();
	UNDEFINED_ENGINE void Update();
	UNDEFINED_ENGINE void LateUpdate();
	UNDEFINED_ENGINE void Draw();

	UNDEFINED_ENGINE Object* AddObject(const std::string& name = "Default");

	std::string Name = "Default";

	std::vector<Object*> Objects;

private:
	static Object Root;
};