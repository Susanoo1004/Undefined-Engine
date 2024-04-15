#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>
#include <type_traits>

namespace Reflection
{
	template<typename T, typename MemberT, typename DescriptorT>
	void DisplayObj(T* obj);

	template<typename T>
	void ReflectionObj(T* obj);

	//Create in cpp and call addtype from
	void DisplayWithHash(void* obj, size_t hash);

	template <typename T>
	struct is_list : public std::false_type {};

	template <typename T>
	struct is_list<std::list<T>> : public std::true_type {};

	template <typename T>
	constexpr bool is_list_v = is_list<T>::value;
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
				DisplayObj<T, MemberT, DescriptorT>(obj);

				if (oldValue != DescriptorT::get(obj))
				{
					constexpr NotifyChange<T> notify = GetAttribute<DescriptorT, NotifyChange<T>>();
					obj->*notify.ptr = true;
				}
			}
			else
			{
				DisplayObj<T, MemberT, DescriptorT>(obj);
			}
		}
	});
}

template<typename T, typename MemberT, typename DescriptorT>
void Reflection::DisplayObj(T* obj)
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
		ImGui::Checkbox(name.c_str(), &DescriptorT::get(obj));
	}
	else if constexpr (std::is_same_v<std::string, MemberT>)
	{
		ImGui::InputText(name.c_str(), &DescriptorT::get(obj));
	}
	else if constexpr (std::is_same_v<Vector3, MemberT>)
	{
		ImGui::DragFloat3(name.c_str(), &DescriptorT::get(obj).x, .1f);
	}
	else if constexpr (Reflection::is_list_v<MemberT>)
	{
		ImGui::Text(name.c_str(), &DescriptorT::get(obj));
		
		for (auto it : DescriptorT::get(obj))
			Logger::Info("{}", typeid(*it).hash_code());

		for (size_t i = 0; i < DescriptorT::get(obj).size(); i++)
		{
			// ReflectionObj<ListT>(&(DescriptorT::get(obj)[i]));
		}
	}

	if constexpr (refl::is_reflectable<MemberT>())
	{
		ReflectionObj<MemberT>(&DescriptorT::get(obj));
	}
}
