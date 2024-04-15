#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

template<typename T, typename MemberT, typename DescriptorT>
void DisplayObj(T* obj);

template<typename T>
void ReflectionObj(T* obj)
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
					NotifyChange<T> notify = GetAttribute<DescriptorT, NotifyChange<T>>();
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
void DisplayObj(T* obj)
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

	if constexpr (refl::is_reflectable<MemberT>())
	{
		ReflectionObj<MemberT>(&DescriptorT::get(obj));
	}
}
