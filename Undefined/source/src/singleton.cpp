#include "singleton.h"

WindowManager* Singleton::windowManager;
Renderer* Singleton::renderer;

void Singleton::Init()
{
	windowManager = new WindowManager();
	renderer = new Renderer();
}

void Singleton::Destroy()
{
	delete windowManager;
	delete renderer;
}
