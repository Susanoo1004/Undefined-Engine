#pragma once

#include "world/scene_manager/object.h"
#include "utils/flag.h"

class Scene
{
public:
	UNDEFINED_ENGINE Scene();
	UNDEFINED_ENGINE ~Scene();

	std::vector<Object> objects;
};