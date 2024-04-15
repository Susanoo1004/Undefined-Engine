#pragma once
#include "world/components/mono_behaviour.h"

class Player : public MonoBehaviour
{
public:
	void Update() override;
};

REFL_AUTO(type(Player, bases<MonoBehaviour>)
);