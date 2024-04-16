#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>
#include <type_traits>
#include <list>
#include <refl.hpp>
#include "engine_debug/logger.h"
#include "interface/attributes.h"
#include <toolbox/Vector3.h>

namespace Reflection
{
	template<typename T, typename MemberT, typename DescriptorT>
	void DisplayObj(MemberT* obj);

	template<typename T>
	void ReflectionObj(T* obj);

	void DisplayWithHash(void* obj, size_t hash);

	template <typename T>
	struct is_vector : public std::false_type {};

	template <typename T, typename A>
	struct is_vector<std::vector<T, A>> : public std::true_type {};

	template <typename T>
	constexpr bool is_vector_v = is_vector<T>::value;
}

template<typename T>
void Reflection::ReflectionObj(T* obj)
{
	constexpr refl::type_descriptor<T> descriptor = refl::reflect<T>();
	refl::util::for_each(descriptor.members, [&]<typename DescriptorT>(const DescriptorT)
	{
		if constexpr (!refl::descriptor::is_function<DescriptorT>(DescriptorT{}))
		{
			using MemberT = typename DescriptorT::value_type;

			if constexpr (HasAttribute<DescriptorT, NotifyChange<T>>())
			{
				const MemberT oldValue = DescriptorT::get(obj);
				DisplayObj<T, MemberT, DescriptorT>(&DescriptorT::get(obj));

				if (oldValue != DescriptorT::get(obj))
				{
					constexpr NotifyChange<T> notify = GetAttribute<DescriptorT, NotifyChange<T>>();
					obj->*notify.ptr = true;
				}
			}
			else
			{
				DisplayObj<T, MemberT, DescriptorT>(&DescriptorT::get(obj));
			}
		}
	});
}

template<typename T, typename MemberT, typename DescriptorT>
void Reflection::DisplayObj(MemberT* obj)
{
	std::string name = DescriptorT::name.c_str();

	if constexpr (HasAttribute<DescriptorT, DontDisplayName>())
	{
		name = "##" + name;
	}

	if constexpr (HasAttribute<DescriptorT, SameLine>())
	{
		ImGui::SameLine();
	}

	if constexpr (HasAttribute<DescriptorT, Spacing>())
	{
		ImGui::Dummy(GetAttribute<DescriptorT, Spacing>().size);
	}

	if constexpr (std::is_same_v<bool, MemberT>)
	{
		ImGui::Checkbox(name.c_str(), obj);
	}
	else if constexpr (std::is_same_v<std::string, MemberT>)
	{
		ImGui::InputText(name.c_str(), obj);
	}
	else if constexpr (std::is_same_v<Vector3, MemberT>)
	{
		ImGui::DragFloat3(name.c_str(), &obj->x, .1f);
	}
	else if constexpr (Reflection::is_vector_v<MemberT>)
	{
		ImGui::Text(name.c_str(), obj);

		using ListT = typename MemberT::value_type;

		for (size_t i = 0; i < obj->size(); i++)
		{
			Reflection::DisplayObj<T, ListT, DescriptorT>(&(*obj)[i]);
		}
	}
	else if constexpr (std::is_pointer_v<MemberT> && std::is_abstract_v<std::remove_pointer_t<MemberT>>)
	{
		Reflection::DisplayWithHash(*obj, typeid(**obj).hash_code());
	}

	if constexpr (refl::is_reflectable<MemberT>())
	{
		ReflectionObj<MemberT>(obj);
	}
}
