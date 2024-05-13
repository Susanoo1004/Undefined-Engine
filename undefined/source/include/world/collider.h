#pragma once

#include "world/component.h"

class Collider : public Component
{
protected:
	unsigned int pBodyID;
};