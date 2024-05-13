#include "world/scene_manager.h"

#include <json/json.h>

#include "wrapper/time.h"

void SceneManager::Init()
{
	if (!Object::mRoot)
	{
		Object::mRoot = new Object("Root");
	}
	if (!ActualScene)
	{
		ActualScene = CreateScene("Default Scene");
	}
}

void SceneManager::Delete()
{
	delete Object::mRoot;
	for (Scene* scene : Scenes)
	{
		delete scene;
	}
}

Scene* SceneManager::CreateScene(const std::string& name)
{
	Scene* newScene = new Scene(name);
	Scenes.push_back(newScene);
	return newScene;
}

void SceneManager::Start()
{
	if (!ActualScene)
	{
		Logger::Error("No scene loaded");
		return;
	}

	ActualScene->Start();
}

void SceneManager::GlobalUpdate()
{
	if (!ActualScene)
	{
		Logger::Error("No scene loaded");
		return;
	}

	while (Time::FixedStep >= 1)
	{
		ActualScene->FixedUpdate();
		Time::FixedStep--;
	}
	Logger::Debug(Json::valueToString(false));

	ActualScene->Update();
	ActualScene->LateUpdate();
}

void SceneManager::Draw()
{
	if (!ActualScene)
	{
		Logger::Error("No scene loaded");
		return;
	}

	ActualScene->Draw();
}

void SceneManager::SaveCurrentScene()
{
	if (!ActualScene)
	{
		return;
	}


}
