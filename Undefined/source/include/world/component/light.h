#pragma once

#include "world/component/component.h"
#include "utils/flag.h"

class Light : public Component
{
public:
	UNDEFINED_ENGINE Light();
	UNDEFINED_ENGINE ~Light();

	void Update();
};