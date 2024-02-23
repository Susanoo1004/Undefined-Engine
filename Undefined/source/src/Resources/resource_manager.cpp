#include "resources/resource_manager.h"

ResourceManager ResourceManager::resourceManager;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Unload(const std::string& name)
{
	mResources[name].reset();
	mResources.erase(name);

	Logger::Info("{} unloaded", name);
}

void ResourceManager::UnloadAll()
{
	for (auto&& p : mResources)
	{
		p.second.reset();
		Logger::Info("{} {} unloaded", typeid(decltype(*p.second.get())).name(), p.first);
	}
	mResources.clear();
}
