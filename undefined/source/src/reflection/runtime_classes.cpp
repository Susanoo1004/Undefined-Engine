#include "reflection/runtime_classes.h"

#include "engine_debug/logger.h"

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