#include "interface/utils_reflection.h"
#include "interface/runtime_classes.h"

void Reflection::DisplayWithHash(void* obj, size_t hash)
{
	RuntimeClasses::Display(obj, hash);
}