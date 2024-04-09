#pragma once

#include <unordered_map>
#include <iostream>
#include <cassert>

#include "resources/resource.h"

#include "engine_debug/logger.h"

#include "utils/flag.h"

/// <summary>
/// 
/// </summary>
template<class T>
concept ResourceType = std::is_base_of_v<Resource, T>;

/// <summary>
/// Manage Resources
/// </summary>
class ResourceManager
{
	STATIC_CLASS(ResourceManager)

public:
	/// <summary>
	/// Load a resource
	/// </summary>
	/// <param name="path">: Resource path</param>
	/// <param name="recursivity">: Is the load recursive</param>
	UNDEFINED_ENGINE static void Load(const std::filesystem::path& path, bool recursivity = false);
	// TO MOVE TO skybox
	UNDEFINED_ENGINE static std::vector<std::string> LoadFolder(const std::filesystem::path& path);
	/// <summary>
	/// Check if the resource manager contains the resource by the name
	/// </summary>
	/// <param name="name">: Name of the resource</param>
	/// <returns>Return true or false wheither the resource manager contains the resource or not</returns>
	UNDEFINED_ENGINE static bool Contains(const std::string& name);

	/// <summary>
	/// Create a resource
	/// </summary>
	/// <typeparam name="...Args"></typeparam>
	/// <typeparam name="Resource"></typeparam>
	/// <param name="name"></param>
	/// <param name="...args"></param>
	/// <returns></returns>
	template<ResourceType Resource, typename... Args>
	static std::shared_ptr<Resource> Create(const std::string& name, Args... args)
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

	UNDEFINED_ENGINE static void Rename(const std::string& oldName, const std::string& newName);
	UNDEFINED_ENGINE static void RenameFolder(const std::string& oldName, const std::string& newName);

	UNDEFINED_ENGINE static void Unload(const std::string& name);
	UNDEFINED_ENGINE static void UnloadAll();

private:
	UNDEFINED_ENGINE static inline std::vector<std::string> mShader;
	UNDEFINED_ENGINE static inline std::unordered_map<std::string, std::shared_ptr<Resource>> mResources;
};
