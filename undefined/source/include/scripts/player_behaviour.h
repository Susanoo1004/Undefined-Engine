#pragma once

#include "world/script.h"

#include "service_locator.h"

class PlayerBehaviour : public Script
{
public:
	PlayerBehaviour();
	~PlayerBehaviour();

	void Update() override;

	std::shared_ptr<KeyInput> PlayerKeyInput;
};