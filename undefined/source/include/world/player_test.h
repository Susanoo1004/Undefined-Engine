#pragma once
#include "world/mono_behaviour.h"

class Player : public MonoBehaviour
{
public:
	void FixedUpdate() override;
};

REFL_AUTO(type(Player, bases<MonoBehaviour>)
);