#include "reflection/runtime_classes.h"

#include "engine_debug/logger.h"
#include "world/dir_light.h"
#include "resources/model_renderer.h"

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
}

void RuntimeClasses::AddAllClasses()
{
	AddClass<DirLight>();
	AddClass<ModelRenderer>();
}

size_t RuntimeClasses::TabSize()
{
	return mHashClasses.size();
}

const RuntimeClass* RuntimeClasses::GetClass(size_t hash)
{
	return &mHashClasses[hash];
}