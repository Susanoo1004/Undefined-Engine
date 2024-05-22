#include "reflection/utils_reflection.h"
#include "reflection/runtime_classes.h"

Json::Value Reflection::WriteValueWithHash(void* val, size_t hash)
{
	return RuntimeClasses::WriteValue(val, hash);
}

void Reflection::DisplayWithHash(void* obj, size_t hash)
{
	RuntimeClasses::Display(obj, hash);
}

