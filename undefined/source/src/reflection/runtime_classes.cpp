#include "reflection/runtime_classes.h"

#include "engine_debug/logger.h"

#include "world/dir_light.h"
#include "world/point_light.h"
#include "world/spot_light.h"

#include "resources/model_renderer.h"
#include <ranges>

const RuntimeClass* RuntimeClasses::GetHashedClass(size_t hash)
{
	auto hashedClass = mHashClasses.find(hash);

	if (hashedClass == mHashClasses.end())
	{
		Logger::Error("Could not find hashClass {}", hash);
		return nullptr;
	}
	return &hashedClass->second;
}

void RuntimeClasses::Display(void* obj, size_t hash)
{
	if (auto hashedClass = GetHashedClass(hash))
	{
		hashedClass->display(obj);
	}
}

Json::Value RuntimeClasses::WriteValue(void* val, size_t hash)
{
	if (auto hashedClass = GetHashedClass(hash))
	{
		return hashedClass->write(val);
	}
	return JSON_USE_NULLREF;
}

void* RuntimeClasses::CreateClass(std::string name)
{
	for (RuntimeClass c : mHashClasses|std::views::values)
	{
		if (c.className == name)
		{
			return c.create();
		}
	}
	
	return nullptr;
}

void RuntimeClasses::AddAllClasses()
{
	//Lights
	AddClass<DirLight>();
	AddClass<PointLight>();
	AddClass<SpotLight>();

	//Model
	AddClass<ModelRenderer>();
}