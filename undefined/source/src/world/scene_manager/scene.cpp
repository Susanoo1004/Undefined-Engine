#include "world/scene_manager/scene.h"


void Scene::Start()
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (Component* comp : Objects[i]->Components)
		{
			comp->Start();
		}
	}
}

UNDEFINED_ENGINE void Scene::FixedUpdate()
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (Component* comp : Objects[i]->Components)
		{
			comp->FixedUpdate();
		}
	}
}

void Scene::Update()
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (Component* comp : Objects[i]->Components)
		{
			comp->Update();
		}
	}
}

UNDEFINED_ENGINE void Scene::LateUpdate()
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (Component* comp : Objects[i]->Components)
		{
			comp->LateUpdate();
		}
	}
}

UNDEFINED_ENGINE void Scene::Draw()
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (Component* comp : Objects[i]->Components)
		{
			comp->Draw();
		}
	}
}

Object* Scene::AddObject(std::string name)
{
	Object* obj = new Object(name);

	Objects.push_back(obj);

	return obj;
}

