#pragma once

#include <vector>

#include "world/scene.h"
#include "utils/flag.h"

class SceneManager
{

	STATIC_CLASS(SceneManager)

public:
	
	static void Init();
	static void Delete();
	
	static Scene* CreateScene(const std::string& name = "New Scene");

	static void Start();
	static void GlobalUpdate();
	static void Draw();

	static void SaveCurrentScene();
	static void LoadScene(const std::string& path);
	
	static inline Scene* ActualScene;
	static inline std::vector<Scene*> Scenes;
};