#include "world/scene_manager/scene.h"

void Scene::Start()
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		Objects[i]->Start();
	}
}

void Scene::Update()
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		Objects[i]->Update();
	}
}

