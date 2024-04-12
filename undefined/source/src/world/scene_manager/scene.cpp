#include "world/scene_manager/scene.h"

#include "world/components/skybox.h"

Scene::~Scene()
{
	for (Object* object : Objects)
	{
		delete object;
	}
}

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

void Scene::FixedUpdate()
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

void Scene::LateUpdate()
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (Component* comp : Objects[i]->Components)
		{
			comp->LateUpdate();
		}
	}
}

void Scene::Draw()
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (Component* comp : Objects[i]->Components)
		{
			comp->Draw();
		}
	}

	// Skybox::Draw();
}

Object* Scene::AddObject(const std::string& name)
{
	Object* obj = new Object(name);

	Objects.push_back(obj);

	return obj;
}

