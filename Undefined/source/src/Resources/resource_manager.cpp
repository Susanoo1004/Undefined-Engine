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

void ResourceManager::LoadAll(std::filesystem::path path)
{
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::size_t pos = path.string().find("assets");
		std::string name = entry.path().string();
		std::string newName = name.substr(pos);

		if (name.ends_with(".obj"))
		{
			std::shared_ptr<Model> resource = std::make_shared<Model>(name.c_str());

			auto&& p = mResources.try_emplace(name, resource);
			if (!p.second)
			{
				p.first->second.reset();
			}
			mResources.emplace(newName, resource);

			if (resource->isValid())
			{
				Logger::Debug("Model {} loaded", newName);
			}

		}

		else if (name.ends_with(".png") || name.ends_with(".jpg"))
		{
			std::shared_ptr<Texture> resource = std::make_shared<Texture>(name.c_str());

			auto&& p = mResources.try_emplace(name, resource);
			if (!p.second)
			{
				p.first->second.reset();
			}
			mResources.emplace(newName, resource);
			if (resource->isValid())
			{
				Logger::Debug("Texture {} loaded", newName);
			}
		}

		else if (entry.is_directory())
		{
			for (const auto& entry : std::filesystem::directory_iterator(path))
			{
				entry.path().string().resize(entry.path().string().size() - 1);
				LoadAll(entry.path().string() + "/");
			}
		}
	}
}

bool ResourceManager::Contains(std::string name)
{
	return mResources.find(name) != mResources.end();
}

void ResourceManager::Unload(const std::string& name)
{
	mResources[name].reset();
	mResources.erase(name);

	Logger::Debug("{} unloaded", name);
}

void ResourceManager::UnloadAll()
{
	for (auto&& p : mResources)
	{
		Logger::Debug("{} {} unloaded", typeid(decltype(*p.second.get())).name(), p.first);
	}
	mResources.clear();
}

void ResourceManager::Rename(std::string oldName, std::string newName)
{
	auto&& p = mResources.find(oldName);

	if (p != mResources.end())
	{
		mResources.emplace(newName, p->second);

		if (p->second->isValid())
		{
			Logger::Debug("Resource {} renamed to {}", oldName, newName);
		}

		mResources.erase(p);
	}
	else
	{
		Logger::Warning("Resource {} not found", oldName);
	}
}
