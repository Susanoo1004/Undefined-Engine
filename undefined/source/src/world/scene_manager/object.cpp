#include "world/scene_manager/object.h"

#include "world/components/visitor_for_update.h"

void Object::Start()
{
	//VisitorForStart start;
	for (size_t i = 0; i < Components.size(); i++)
	{
		//Components[i]->Accept(start);
	}
}

void Object::Update()
{
	VisitorForUpdate update;
	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i]->Accept(update);


	}
}

