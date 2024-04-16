#pragma once

#include <vector>

#include "world/scene_manager/scene.h"
#include "utils/flag.h"

class SceneManager
{

	STATIC_CLASS(SceneManager)

public:
	
	static void Init();
	static void Delete();
	
	static Scene* CreateScene(const std::string& name = "New Scene");
	
	static inline Scene* ActualScene;
	static inline std::vector<Scene*> Scenes;
};