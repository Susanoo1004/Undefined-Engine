#pragma once
#include "utils/flag.h"

#include <vector>
#include <numeric>

namespace Utils
{
	template<typename Type>
	Type Average(const std::vector<Type>& array)
	{
		return std::reduce(array.begin(), array.end()) / array.size();
	}
	
	constexpr bool IsZero(float value) { return (value <= 1e-6f); }

	constexpr bool OnInterval(float value, float lastValue, float interval) { return Utils::IsZero(interval) || ((int)(lastValue / interval) != (int)(value / interval)); }

	template <typename PtrT, typename IntT>
	constexpr PtrT IntToPointer(const IntT number)
	{
		static_assert(std::is_pointer_v<PtrT>, "PtrT must be a raw pointer type, ex: PtrT=int*");
		static_assert(std::is_integral_v<IntT>, "IntT must be an integral type, ex: IntT=int");

		return reinterpret_cast<PtrT>(reinterpret_cast<uint8_t*>(1) + static_cast<const size_t>(number) - 1);
	}
};
