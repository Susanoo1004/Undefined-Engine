#pragma once

#include <vector>

#include "world/script.h"

class Player : public Script
{
public:
	void Update() override;

private:
	
};

REFL_AUTO(type(Player, bases<Script>)
);