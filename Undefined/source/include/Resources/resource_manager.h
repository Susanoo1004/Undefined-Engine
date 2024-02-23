#pragma once

#include <unordered_map>
#include <iostream>
#include <cassert>

#include "resources/resource.h"
#include "logger/logger.h"

template<class T>
concept Type = std::is_base_of<Resource, T>::value;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

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

		Logger::Info("{} {} loaded", typeid(T).name(), name);

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

		Logger::Info("{} {} loaded", typeid(T).name(), name);

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

	void Unload(const std::string& name);
	static void UnloadAll();

private:

	static inline std::unordered_map<std::string, std::shared_ptr<Resource>> mResources;

public:
	static ResourceManager resourceManager;
};
