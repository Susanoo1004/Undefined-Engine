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

const RuntimeClass* RuntimeClasses::GetClassByType(std::string type)
{
	for (size_t i = 0; i < mHashClasses.size(); i++)
	{
		auto typeClass = mHashClasses[i];
		if (typeClass.type == type)
		{
			return &typeClass;
		}
	}

	Logger::Error("Could not find typeClass {}", type);
	return nullptr;
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
	return Json::Value();
}

void RuntimeClasses::ReadValue(void* obj, std::string type)
{
	if (auto hashedClass = GetClassByType(type))
	{
		hashedClass->read(obj);
	}
}