#pragma once

#include <unordered_map>
#include <iostream>
#include <cassert>

#include "resources/resource.h"
#include "logger/logger.h"
#include "utils/flag.h"

template<class T>
concept ResourceType = std::is_base_of_v<Resource, T>;

class ResourceManager
{
	STATIC_CLASS(ResourceManager)

public:
	UNDEFINED_ENGINE static void Load(const std::filesystem::path& path, bool recursivity = false);
	UNDEFINED_ENGINE static std::vector<std::string> LoadFolder(std::filesystem::path path);
	UNDEFINED_ENGINE static bool Contains(std::string name);

	template<ResourceType Resource, typename... Args>
	static std::shared_ptr<Resource> Create(std::string name, Args... args)
	{
		std::shared_ptr<Resource> resource = std::make_shared<Resource>(args...);
		
		auto&& p = mResources.try_emplace(name, resource);
		if (!p.second)
		{
			p.first->second.reset();
		}
		mResources.emplace(name, resource);

		Logger::Debug("{} {} loaded", typeid(Resource).name(), name);

		return resource;
	}

	template<ResourceType Resource>
	static std::shared_ptr<Resource> Get(const std::string& name)
	{
		auto&& p = mResources.find(name);

		if (p == mResources.end())
		{
			Logger::Warning("Invalid resource name : {}", name);
			return nullptr;
		}

		return std::dynamic_pointer_cast<Resource>(p->second);
	}

	UNDEFINED_ENGINE static void Rename(std::string oldName, std::string newName);
	UNDEFINED_ENGINE static void Unload(const std::string& name);
	UNDEFINED_ENGINE static void UnloadAll();

private:
	UNDEFINED_ENGINE static inline std::vector<std::string> mShader;
	UNDEFINED_ENGINE static inline std::unordered_map<std::string, std::shared_ptr<Resource>> mResources;
};
