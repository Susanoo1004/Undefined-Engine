#include "service_locator.h"

void ServiceLocator::Setup()
{
	ServiceLocator::Provide<InputManager>(new InputManager());
	ServiceLocator::Provide<Window>(new Window());
	ServiceLocator::Provide<Renderer>(new Renderer());
}

void ServiceLocator::CleanServiceLocator()
{
	for (auto&& s : mServices)
	{
		delete s.second;
	}

	mServices.clear();
}
