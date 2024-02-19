#pragma once

#include "Resources/resource.h"
#include <unordered_map>
#include <iostream>

template<class T>
concept Type = std::is_base_of<Resource, T>::value;

class ResourceManager
{
public:

	ResourceManager() {};
	~ResourceManager()
	{
		UnloadAll();
	}

	static ResourceManager resourceManager;

	template<Type T>
	T* Create(const std::string& name)
	{
		T* resource = new T(name.c_str());
		auto&& p = m_Resources.try_emplace(name, resource);
		if (!p.second)
		{
			delete p.first->second;
		}
		m_Resources.emplace(name, resource);

		std::cout << std::endl << name << " loaded" << std::endl;
		return resource;
	}

	template<Type T>
	inline T* Get(const std::string& name)
	{
		return dynamic_cast<T*>(m_Resources.find(name)->second);
	}
	void Unload(const std::string& name);

private:
	std::unordered_map<std::string, Resource*> m_Resources;
	void UnloadAll();
};
