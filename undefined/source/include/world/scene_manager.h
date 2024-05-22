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
	
	static Scene* CreateScene(const std::string& mName = "New Scene");

	static void Reload();

	static void Start();
	static void GlobalUpdate();
	static void Draw();

	static void SaveCurrentScene();
	static bool LoadScene(const std::filesystem::path& path);
		
	static inline bool IsScenePlaying = false;
	static inline bool IsScenePaused = false;

	static inline Scene* ActualScene;
	static inline std::vector<Scene*> Scenes;
};