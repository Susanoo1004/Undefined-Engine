#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>
#include <type_traits>
#include <refl.hpp>
#include <toolbox/Vector3.h>
#include <toolbox/calc.h>

#include "engine_debug/logger.h"
#include "interface/attributes.h"

namespace Reflection
{
	/// <summary>
	/// Display the variables we added to the reflection struct 
	/// </summary>
	/// <typeparam name="T"> base type </typeparam>
	/// <typeparam name="MemberT"> type of the variable we wish to reflect </typeparam>
	/// <typeparam name="DescriptorT"> metadata from the element we want to reflect </typeparam>
	/// <param name="obj"> object we want to display </param>
	template<typename T, typename MemberT, typename DescriptorT>
	void DisplayObj(MemberT* obj);

	/// <summary>
	/// Object we wish to reflect
	/// </summary>
	/// <typeparam name="T"> type of the object we want to reflect </typeparam>
	/// <param name="obj"> object we reflect </param>
	template<typename T>
	void ReflectionObj(T* obj);

	/// <summary>
	/// Get a class that inherits from Component with it's hash code
	/// </summary>
	/// <param name="obj"> object we want to display </param>
	/// <param name="hash"> hash code of the class </param>
	void DisplayWithHash(void* obj, size_t hash);

	/// <summary>
	/// Display bases types in inspector
	/// </summary>
	/// <typeparam name="T"> base class </typeparam>
	/// <typeparam name="MemberT"> type of the variable </typeparam>
	/// <typeparam name="DescriptorT"> metadata from the element we want to reflect </typeparam>
	/// <param name="obj"> object we want to display </param>
	/// <param name="name"> name of the object we want to display </param>
	template<typename T, typename MemberT, typename DescriptorT>
	void DisplayBaseTypes(MemberT* obj, std::string name);

	template<typename T, typename MemberT, typename DescriptorT>
	void DisplayStandardTypes(MemberT* obj, std::string name);

	template<typename T, typename MemberT, typename DescriptorT>
	void DisplayToolboxTypes(MemberT* obj, std::string name);

	template<typename T, typename MemberT, typename DescriptorT>
	void Attributes(std::string& name);

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
	//Lamba that loops for each element we reflect from a class
	refl::util::for_each(descriptor.members, [&]<typename DescriptorT>(const DescriptorT)
	{
		//We make sure that what we are trying to reflect isn't a function or a variable that has the attribute HideInInspector
		if constexpr (!refl::descriptor::is_function<DescriptorT>(DescriptorT{}) && !HasAttribute<DescriptorT, HideInInspector>())
		{
			//MemberT is the type of the element we reflect
			using MemberT = typename DescriptorT::value_type;

			//If there's a change we put notify to true
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
void Reflection::DisplayBaseTypes(MemberT* obj, std::string name)
{
	if constexpr (std::is_same_v<float, MemberT>)
	{
		ImGui::DragScalar(name.c_str(), ImGuiDataType_Float, obj, .1f);
	}
	else if constexpr (std::is_same_v<double, MemberT>)
	{
		ImGui::DragScalar(name.c_str(), ImGuiDataType_Double, obj, .1f);
	}
	else if constexpr (std::is_same_v<int8_t, MemberT>)
	{
		ImGui::DragScalar(name.c_str(), ImGuiDataType_S8, obj, .1f);
	}
	else if constexpr (std::is_same_v<int16_t, MemberT>)
	{
		ImGui::DragScalar(name.c_str(), ImGuiDataType_S16, obj, .1f);
	}
	else if constexpr (std::is_same_v<int, MemberT>)
	{
		ImGui::DragScalar(name.c_str(), ImGuiDataType_S32, obj, .1f);
	}
	else if constexpr (std::is_same_v<int64_t, MemberT>)
	{
		ImGui::DragScalar(name.c_str(), ImGuiDataType_S64, obj, .1f);
	}
	else if constexpr (std::is_same_v<uint8_t, MemberT>)
	{
		ImGui::DragScalar(name.c_str(), ImGuiDataType_U8, obj, .1f);
	}
	else if constexpr (std::is_same_v<uint16_t, MemberT>)
	{
		ImGui::DragScalar(name.c_str(), ImGuiDataType_U16, obj, .1f);
	}
	else if constexpr (std::is_same_v<unsigned int, MemberT>)
	{
		ImGui::DragScalar(name.c_str(), ImGuiDataType_U32, obj, .1f);
	}
	else if constexpr (std::is_same_v<uint64_t, MemberT>)
	{
		ImGui::DragScalar(name.c_str(), ImGuiDataType_U64, obj, .1f);
	}
}

template<typename T, typename MemberT, typename DescriptorT>
void Reflection::DisplayStandardTypes(MemberT* obj, std::string name)
{
	//We check if MemberT (type of the variable we are reflecting) is the same as one of the standard lib
	if constexpr (std::is_same_v<std::string, MemberT>)
	{
		ImGui::InputText(name.c_str(), obj);
	}
}

template<typename T, typename MemberT, typename DescriptorT>
void Reflection::DisplayToolboxTypes(MemberT* obj, std::string name)
{
	//We check if MemberT (type of the variable we are reflecting) is the same as one of the math toolbox
	if constexpr (std::is_same_v<Vector4, MemberT>)
	{
		//If the field has the attribute ToDeg we use a sliderAngle which convert radiants to degrees else we use DragFloat and send radiants directly
		if constexpr (HasAttribute<DescriptorT, ToDeg>())
		{
			ImGui::SliderAngle4(name.c_str(), &obj->x);
		}
		else
		{
			ImGui::DragFloat4(name.c_str(), &obj->x, .1f);
		}
	}
	else if constexpr (std::is_same_v<Vector3, MemberT>)
	{
		if constexpr (HasAttribute<DescriptorT, ToDeg>())
		{
			ImGui::SliderAngle3(name.c_str(), &obj->x);
		}
		else
		{
			ImGui::DragFloat3(name.c_str(), &obj->x, .1f);
		}
	}
	else if constexpr (std::is_same_v<Vector2, MemberT>)
	{
		if constexpr (HasAttribute<DescriptorT, ToDeg>())
		{
			ImGui::SliderAngle2(name.c_str(), &obj->x);
		}
		else
		{
			ImGui::DragFloat2(name.c_str(), &obj->x, .1f);
		}
	}
}

template<typename T, typename MemberT, typename DescriptorT>
void Reflection::Attributes(std::string& name)
{
	//If the Descriptor has a certain attribute
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
}

template<typename T, typename MemberT, typename DescriptorT>
void Reflection::DisplayObj(MemberT* obj)
{
	std::string name = DescriptorT::name.c_str();

	Attributes<T, MemberT, DescriptorT>(name);

	//We check if MemberT (type of the variable we are reflecting) is the same as one of the bases types
	if constexpr (std::is_same_v<bool, MemberT>)
	{
		ImGui::Checkbox(name.c_str(), obj);
	}
	else if constexpr (std::is_integral_v<MemberT> || std::is_floating_point_v<MemberT>)
	{
		DisplayBaseTypes<T, MemberT, DescriptorT>(obj, name);
	}
	else if constexpr (std::_Is_any_of_v<MemberT, std::string>)
	{
		DisplayStandardTypes<T, MemberT, DescriptorT>(obj, name);
	}
	else if constexpr (std::_Is_any_of_v<MemberT, Vector4, Vector3, Vector2>)
	{
		DisplayToolboxTypes<T, MemberT, DescriptorT>(obj, name);
	}
	else if constexpr (Reflection::is_vector_v<MemberT>)
	{
		ImGui::Text(name.c_str(), obj);

		using ListT = typename MemberT::value_type;

		//If it's a std::vector we reflect every element inside it
		for (size_t i = 0; i < obj->size(); i++)
		{
			Reflection::DisplayObj<T, ListT, DescriptorT>(&(*obj)[i]);
		}
	}
	else if constexpr (std::is_pointer_v<MemberT> && std::is_abstract_v<std::remove_pointer_t<MemberT>>)
	{
		Reflection::DisplayWithHash(*obj, typeid(**obj).hash_code());
	}
	//Recursivity if there's a reflectable type
	if constexpr (refl::is_reflectable<MemberT>())
	{
		ReflectionObj<MemberT>(obj);
	}
}
