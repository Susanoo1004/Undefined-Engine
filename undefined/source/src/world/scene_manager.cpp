#include "world/scene_manager.h"

#include <json/json.h>
#include <iostream>
#include <fstream>

#include "wrapper/time.h"
#include "reflection/utils_reflection.h"

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

	Json::Value root;

	for (Object* obj : ActualScene->Objects)
	{
		root[std::to_string(obj->mUUID)] = Reflection::WriteObj(obj);
	}

	std::ofstream file("assets/scenes/test.scene");
	//if (!ActualScene->Path.string().ends_with(".scene"))
	//{
		//ActualScene->Path = "assets/" + ActualScene->Name + ".scene";
	//}
	//std::ofstream file(ActualScene->Path);
	file << root.toStyledString();

	file.close();
}

bool SceneManager::LoadScene(const std::filesystem::path& path)
{
	if (!path.string().ends_with(".scene"))
	{
		return false;
	}

	Json::Value root;
	std::ifstream file(path);
	file >> root;

	//std::string value = root.front().get("Values", Json::Value()).get("Name", std::string()).as<std::string>();

	//Logger::Debug("{}", value);

	Object obj = Reflection::ReadObj<Object>(root.front().get("Values", Json::Value()));

	file.close();
	return false;
}
