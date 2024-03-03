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

};