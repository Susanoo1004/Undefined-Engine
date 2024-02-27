#pragma once

#include <unordered_map>
#include <iostream>
#include <cassert>

#include "resources/resource.h"
#include "logger/logger.h"
#include "utils/flag.h"

template<class T>
concept Type = std::is_base_of<Resource, T>::value;

class ResourceManager
{
public:
	UNDEFINED_ENGINE ResourceManager();
	UNDEFINED_ENGINE ~ResourceManager();

	UNDEFINED_ENGINE static void LoadAll(std::string path);

	template<Type T>
	std::shared_ptr<T> Create(const std::string& name)
	{
		std::shared_ptr<T> resource = std::make_shared<T>(name.c_str());

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
	std::shared_ptr<T> Create(const std::string& name, const std::string& filepath)
	{
		std::shared_ptr<T> resource = std::make_shared<T>(filepath.c_str());

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
	inline std::shared_ptr<T> Get(const std::string& name)
	{
		auto&& p = mResources.find(name);

		if (p == mResources.end())
		{
			Logger::Warning("Resource name incorrect : {}", name);
		}

		return std::dynamic_pointer_cast<T>(p->second);
	}

	UNDEFINED_ENGINE void Unload(const std::string& name);
	UNDEFINED_ENGINE static void UnloadAll();

private:
	UNDEFINED_ENGINE static inline std::unordered_map<std::string, std::shared_ptr<Resource>> mResources;

public:
	UNDEFINED_ENGINE static ResourceManager resourceManager;
};
