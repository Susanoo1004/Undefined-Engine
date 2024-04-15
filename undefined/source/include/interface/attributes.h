#pragma once

#include <refl.hpp>

using FieldAttribute = refl::attr::usage::field;

struct DontDisplayName : FieldAttribute
{
};

struct SameLine : FieldAttribute
{
};

template <typename T>
struct NotifyChange : FieldAttribute
{
	using PtrT = bool T::*;

	PtrT ptr;

	constexpr NotifyChange(PtrT p)
		: ptr(p) {}
};

template <typename DescriptorT, typename AttributeT>
constexpr bool HasAttribute()
{
	return refl::descriptor::has_attribute<AttributeT>(DescriptorT{});
}

template <typename DescriptorT, typename AttributeT>
constexpr AttributeT GetAttribute()
{
	return refl::descriptor::get_attribute<AttributeT>(DescriptorT{});
}
