#pragma once

#include "utils/utils.h"
#include <unordered_map>
#include <functional>
#include "reflection/utils_reflection.h"
#include <vector>

struct RuntimeClass
{
	std::string className;

	std::function<void(void*)> display;
	std::function<Json::Value(void*)> write;
	std::function<void*()> create;
};

class RuntimeClasses
{
	STATIC_CLASS(RuntimeClasses)

public:
	template <typename T>
	static void AddClass();

	static void AddAllClasses();

	static const RuntimeClass* GetHashedClass(size_t hash);

	static void Display(void* obj, size_t hash);
	static Json::Value WriteValue(void* val, size_t hash);
	static void* CreateClass(std::string name);

	static inline std::vector<std::string> names;
	
private:
	static inline std::unordered_map<size_t, RuntimeClass> mHashClasses;
};

template <typename T>
void RuntimeClasses::AddClass()
{
	RuntimeClass info = 
	{
		.className = refl::reflect<T>().name.c_str(),
		.display = [](void* obj) -> void { Reflection::ReflectionObj<T>(static_cast<T*>(obj)); },
		.write = [](void* obj) -> Json::Value { return Reflection::WriteValue<T>(static_cast<T*>(obj)); },
		.create = []() -> void* { return new T; }
	};

	if constexpr (!std::is_default_constructible_v<T>)
	{
		info.create = []() -> void* { return nullptr; };
	}

	std::string name = typeid(T).name();

	name.erase(0, 6);

	names.push_back(name);

	mHashClasses.emplace(typeid(T).hash_code(), info);
}
