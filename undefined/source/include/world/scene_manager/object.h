#pragma once

#include <vector>

#include "world/components/component.h"
#include "utils/flag.h"

class Object
{
public:

	UNDEFINED_ENGINE void Start();
	UNDEFINED_ENGINE void Update();

	std::vector<Component*> Components;
};