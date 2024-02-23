#include "resources/resource_manager.h"
#include "Resources/model.h"
#include "Resources/texture.h"


ResourceManager ResourceManager::resourceManager;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::LoadAll(std::string path)
{
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string name = entry.path().string();

		if (name.ends_with(".obj"))
		{
			std::shared_ptr<Model> resource = std::make_shared<Model>(name.c_str());

			auto&& p = mResources.try_emplace(name, resource);
			if (!p.second)
			{
				p.first->second.reset();
			}
			mResources.emplace(name, resource);

			Logger::Info("Model {} loaded", name);

		}

		else if (name.ends_with(".png") || name.ends_with(".jpg"))
		{
			std::shared_ptr<Texture> resource = std::make_shared<Texture>(name.c_str());

			auto&& p = mResources.try_emplace(name, resource);
			if (!p.second)
			{
				p.first->second.reset();
			}
			mResources.emplace(name, resource);

			Logger::Info("Texture {} loaded", name);
		}
	}
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
		Logger::Info("{} {} unloaded", typeid(decltype(*p.second.get())).name(), p.first);
	}
	mResources.clear();
}
