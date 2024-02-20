#pragma once

#include <unordered_map>
#include <iostream>

#include "resources/resource.h"

template<class T>
concept Type = std::is_base_of<Resource, T>::value;

class ResourceManager
{
public:

	ResourceManager();
	~ResourceManager();

	template<Type T>
	T* Create(const std::string& name)
	{
		T* resource = new T(name.c_str());
		auto&& p = mResources.try_emplace(name, resource);
		if (!p.second)
		{
			delete p.first->second;
		}
		mResources.emplace(name, resource);

		std::cout << std::endl << name << " loaded" << std::endl;

		return resource;
	}

	template<Type T>
	inline T* Get(const std::string& name)
	{
		return dynamic_cast<T*>(mResources.find(name)->second);
	}

	void Unload(const std::string& name);

private:
	void UnloadAll();

	std::unordered_map<std::string, Resource*> mResources;

public:
	static ResourceManager resourceManager;
};
