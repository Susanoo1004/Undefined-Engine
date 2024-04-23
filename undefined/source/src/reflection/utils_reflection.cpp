#include "reflection/utils_reflection.h"
#include "reflection/runtime_classes.h"

void Reflection::DisplayWithHash(void* obj, size_t hash)
{
	RuntimeClasses::Display(obj, hash);
}