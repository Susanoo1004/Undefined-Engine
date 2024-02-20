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
	delete mResources[name];
	mResources.erase(name);
	std::cout << std::endl << name << " unloaded" << std::endl;
}

void ResourceManager::UnloadAll()
{
	for (auto&& p : mResources)
	{
		delete p.second;
		std::cout << std::endl << p.first << " unloaded" << std::endl;
	}
	mResources.clear();
}
