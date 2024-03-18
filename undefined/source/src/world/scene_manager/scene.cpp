#include "world/scene_manager/scene.h"


void Scene::Start()
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (size_t j = 0; j < Objects[i]->Components.size(); j++)
		{
			Objects[i]->Components[j]->Start();
		}
	}
}

void Scene::Update()
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (size_t j = 0; j < Objects[i]->Components.size(); j++)
		{
			Objects[i]->Components[j]->Update();
		}
	}
}

