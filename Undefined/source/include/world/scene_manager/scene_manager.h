#pragma once

#include <vector>

#include "world/scene_manager/scene.h"
#include "utils/flag.h"

class SceneManager
{
public:
	UNDEFINED_ENGINE SceneManager();
	UNDEFINED_ENGINE ~SceneManager();

	std::vector<Scene> Scenes;
};