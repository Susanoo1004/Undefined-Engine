#pragma once

#include "utils/utils.h"
#include <unordered_map>
#include <functional>
#include "reflection/utils_reflection.h"

struct RuntimeClass
{
	std::string type;
	std::function<void(void*)> display;
	std::function<Json::Value(void*)> write;
};

class RuntimeClasses
{
	STATIC_CLASS(RuntimeClasses)

public:
	template <typename T>
	static void AddType();

	static const RuntimeClass* GetHashedClass(size_t hash);
	static const RuntimeClass* GetClassByType(std::string type);

	static void Display(void* obj, size_t hash);
	static Json::Value WriteValue(void* val, size_t hash);

private:
	static inline std::unordered_map<size_t, RuntimeClass> mHashClasses;
};

template <typename T>
void RuntimeClasses::AddType()
{
	RuntimeClass info =
	{
		.type = typeid(T).name(),
		.display = [](void* obj) -> void { Reflection::ReflectionObj<T>(static_cast<T*>(obj)); },
		.write = [](void* obj) -> Json::Value { return Reflection::WriteValue<T>(static_cast<T*>(obj)); }
	};

	mHashClasses.emplace(typeid(T).hash_code(), info);
}