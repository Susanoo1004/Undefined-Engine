#pragma once

#include <unordered_map>
#include <iostream>
#include <cassert>

#include "resources/resource.h"

#include "engine_debug/logger.h"

#include "utils/flag.h"

template<class T>
concept Type = std::is_base_of<Resource, T>::value;

class ResourceManager
{
	STATIC_CLASS(ResourceManager)

public:
	UNDEFINED_ENGINE static void Load(std::filesystem::path path, bool recursivity = false);
	UNDEFINED_ENGINE static bool Contains(std::string name);

	template<Type T, typename... Args>
	static std::shared_ptr<T> Create(std::string name, Args... args)
	{
		std::shared_ptr<T> resource = std::make_shared<T>(args...);
			
		auto&& p = mResources.try_emplace(name, resource);
		if (!p.second)
		{
			p.first->second.reset();
		}
		mResources.emplace(name, resource);

		Logger::Debug("{} {} loaded", typeid(T).name(), name);

		return resource;
	}

	template<Type T>
	static std::shared_ptr<T> Get(const std::string& name)
	{
		auto&& p = mResources.find(name);

		if (p == mResources.end())
		{
			Logger::Warning("Invalid resource name : {}", name);
			return nullptr;
		}

		return std::dynamic_pointer_cast<T>(p->second);
	}

	UNDEFINED_ENGINE static void Rename(const std::string& oldName, const std::string& newName);
	UNDEFINED_ENGINE static void RenameFolder(const std::string& oldName, const std::string& newName);

	UNDEFINED_ENGINE static void Unload(const std::string& name);
	UNDEFINED_ENGINE static void UnloadAll();

private:
	UNDEFINED_ENGINE static inline std::unordered_map<std::string, std::shared_ptr<Resource>> mResources;
};
