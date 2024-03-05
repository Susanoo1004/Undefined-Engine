#pragma once

#include "utils/flag.h"

class Component
{
public:
	UNDEFINED_ENGINE Component();
	virtual ~Component();

	virtual void Update();
};