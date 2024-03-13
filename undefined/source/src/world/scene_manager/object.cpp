#include "world/scene_manager/object.h"

void Object::Start()
{
	for (size_t i = 0; i < Components.size(); i++)
	{
		//Components[i].Start();
	}
}

void Object::Update()
{
	for (size_t i = 0; i < Components.size(); i++)
	{
		//Components[i].Update();
	}
}

