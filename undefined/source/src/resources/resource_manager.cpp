#include "resources/resource_manager.h"

#include "Resources/model.h"
#include "Resources/texture.h"
#include "Resources/shader.h"


void ResourceManager::Load(const std::filesystem::path& path, bool recursivity)
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
		std::string filename = entry.path().filename().generic_string();
		std::string parentName = entry.path().parent_path().filename().string();
		size_t pos = name.find(parentName);
		std::string newName = name.substr(pos);

		if (name.ends_with(".obj"))
		{
			Create<Model>(newName, name.c_str());
		}

		else if (name.ends_with(".png") || name.ends_with(".jpg"))
		{
			Create<Texture>(newName, name.c_str());
		}

		else if (name.ends_with(".fs"))
		{
			mShader.push_back(entry.path().generic_string());
		}

		else if (name.ends_with(".vs"))
		{
			if (mShader.size() != 0)
			{
				std::string fragShaderName = entry.path().generic_string();
				fragShaderName.resize(fragShaderName.size() - 2);
				fragShaderName += "fs";
				if (std::find(mShader.begin(), mShader.end(), fragShaderName) != mShader.end())
				{
					filename.resize(filename.size() - 3);
					Create<Shader>(filename, name.c_str(), fragShaderName.c_str());
				}
			}
		}
	}
}

std::vector<std::string> ResourceManager::LoadFolder(std::filesystem::path path)
{
	std::vector<std::string> vectorArray;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string name = entry.path().string();
		std::string filename = entry.path().filename().generic_string();
		std::string parentName = entry.path().parent_path().filename().string();
		size_t pos = name.find(parentName);
		std::string newName = name.substr(pos);

		if (name.ends_with(".obj"))
		{
			Create<Model>(newName, name.c_str());
			vectorArray.push_back(name);
		}

		else if (name.ends_with(".png") || name.ends_with(".jpg"))
		{
			Create<Texture>(newName, name.c_str());
			vectorArray.push_back(name);
		}
	}

	return vectorArray;
}

bool ResourceManager::Contains(std::string name)
{
	if (mResources.find(name) != mResources.end())
	{
		return true;
	}

	else
	{
		Logger::Warning("The resource manager does not contain : {}", name);
		return false;
	}
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
		Logger::Debug("{} {} unloaded", typeid(*p.second.get()).name(), p.first);
	}
	mResources.clear();
}

void ResourceManager::Rename(std::string oldName, std::string newName)
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
