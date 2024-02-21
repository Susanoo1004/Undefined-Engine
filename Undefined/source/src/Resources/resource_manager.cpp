#include "resources/resource_manager.h"

ResourceManager ResourceManager::resourceManager;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	UnloadAll();
}
void ResourceManager::Unload(const std::string& name)
{
	mResources[name].reset();
	mResources.erase(name);
	std::cout << std::endl << name << " unloaded" << std::endl;
}

void ResourceManager::UnloadAll()
{
	for (auto&& p : mResources)
	{
		p.second.reset();
		std::cout << typeid(decltype(*p.second.get())).name() << " " << p.first << " unloaded" << std::endl;
	}
	mResources.clear();
}
