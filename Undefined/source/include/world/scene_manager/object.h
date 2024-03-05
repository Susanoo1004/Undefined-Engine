#pragma once

#include <vector>

#include "world/component/component.h"
#include "utils/flag.h"

class Object
{
public:
	UNDEFINED_ENGINE Object();
	UNDEFINED_ENGINE ~Object();
	std::vector<Component> Components;
};