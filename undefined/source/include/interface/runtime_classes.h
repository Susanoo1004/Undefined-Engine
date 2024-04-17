#pragma once

#include "utils/utils.h"
#include <unordered_map>
#include <functional>
#include "interface/utils_reflection.h"

struct RuntimeClass
{
	std::function<void(void*)> display;
};

class RuntimeClasses
{
	STATIC_CLASS(RuntimeClasses)

public:
	template <typename T>
	static void AddType();

	static void Display(void* obj, size_t hash);

private:
	static inline std::unordered_map<size_t, RuntimeClass> mHashClasses;
};

template <typename T>
void RuntimeClasses::AddType()
{
	RuntimeClass info = 
	{
		.display = [](void* obj) -> void { Reflection::ReflectionObj<T>(static_cast<T*>(obj)); }
	};

	mHashClasses.emplace(typeid(T).hash_code(), info);

	Logger::Info("Added type : {}", typeid(T).hash_code());
}