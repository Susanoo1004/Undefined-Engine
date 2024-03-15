#include "resources/resource_manager.h"

#include <vector>

#include "Resources/model.h"
#include "Resources/texture.h"
#include "Resources/shader.h"


void ResourceManager::Load(std::filesystem::path path, bool recursivity)
{
	std::string fragPath;
	std::string vertexPath;

	if (!path.empty())
	{
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			if (recursivity)
			{
				if (std::filesystem::is_directory(entry))
				{
					Load(entry.path().string() + "/", true);
				}
			}

			std::string name = entry.path().string();
			std::string parentName = entry.path().parent_path().filename().string();
			size_t pos = name.find(parentName);
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

				if (resource->IsValid())
				{
					Logger::Debug("Model : {} loaded", newName);
				}
			}
		

			if (name.ends_with(".png") || name.ends_with(".jpg"))
			{
				std::shared_ptr<Texture> resource;
				resource = std::make_shared<Texture>(name.c_str(), false);

				if (resource->IsValid())
				{
					auto&& p = mResources.try_emplace(name, resource);
					if (!p.second)
					{
						p.first->second.reset();
					}

					mResources.emplace(newName, resource);

					Logger::Debug("Texture : {} loaded", newName);
				}
			}

			else if (name.ends_with(".fs"))
			{
				fragPath = name;
			}

			else if (name.ends_with(".vs"))
			{
				vertexPath = name;
			}

			if (vertexPath.size() && fragPath.size())
			{
				std::shared_ptr<Shader> resource;
				resource = std::make_shared<Shader>(vertexPath.c_str(), fragPath.c_str());

				if (resource->IsValid())
				{
					newName = "baseShader";
					auto&& p = mResources.try_emplace(name, resource);
					if (!p.second)
					{
						p.first->second.reset();
					}
					mResources.emplace(newName, resource);

					Logger::Debug("Shader : {} loaded", newName);
				}
			}
		}
	}
	else
	{
		Logger::Warning("Path {} does not exist", path.string());
	}
}

bool ResourceManager::Contains(std::string name)
{
	if (mResources.find(name) != mResources.end())
	{
		return true;
	}
		
	Logger::Warning("The resource manager does not contain : {}", name);
	return false;
}

void ResourceManager::Unload(const std::string& name)
{
	mResources[name].reset();
	mResources.erase(name);

	Logger::Debug("{} unloaded", name);
}

void ResourceManager::UnloadAll()
{
	Logger::Debug("\n \n [UNLOAD] \n");

	for (auto&& p : mResources)
	{
		Logger::Debug("{} {} unloaded", typeid(*p.second.get()).name(), p.first);
	}
	mResources.clear();

	Logger::Debug("\n");
}

void ResourceManager::Rename(const std::string& oldName, const std::string& newName)
{
	auto&& p = mResources.find(oldName);

	if (p != mResources.end())
	{
		mResources.emplace(newName, p->second);

		if (p->second->IsValid())
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


void ResourceManager::RenameFolder(const std::string& oldName, const std::string& newName)
{
	std::vector<std::pair<std::string, std::shared_ptr<Resource>>> test;
	for (auto& it : mResources)
	{
		if (it.first.find(oldName) == 0)
		{
			test.push_back(it);
		}
	}


	for (auto& it : test)
	{
		auto node = mResources.extract(it.first);
		node.key() = newName + it.first.substr(it.first.find_last_of("/"));

		mResources.insert(std::move(node));
	}
}