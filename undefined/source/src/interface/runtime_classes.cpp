#include "interface/runtime_classes.h"

#include "engine_debug/logger.h"

void RuntimeClasses::Display(void* obj, size_t hash)
{
	auto flipping = mHashClasses.find(hash);

	if (flipping == mHashClasses.end())
	{
		Logger::Error("Could not find hashClass {}", hash);
	}

	else
	{
		flipping->second.display(obj);
	}
}