#include "Manager/resource_manager.h"

ResourceManager ResourceManager::resourceManager;

void ResourceManager::Unload(const std::string& name)
{
	delete m_Resources[name];
	m_Resources.erase(name);
	std::cout << std::endl << name << " unloaded" << std::endl;
}

void ResourceManager::UnloadAll()
{
	for (auto&& p : m_Resources)
	{
		delete p.second;
		std::cout << std::endl << p.first << " unloaded" << std::endl;
	}
	m_Resources.clear();
}
