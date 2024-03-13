#pragma once
#include "world/component/mono_behaviour.h"

class Player : MonoBehaviour
{
public:
	Player();
	~Player();

	int Chiffre = 0;


	void Update();

private:

};
