#pragma once

#include <unordered_map>
#include <iostream>
#include <string>

#include "Resources/resource.h"
#include "Resources/texture.h"
#include "Resources/model.h"

inline std::string GetClassName(Resource& res)
{
	std::string name = std::string(typeid(res).name());
	name.erase(0, 6);

	return name;
}