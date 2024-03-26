#include "world/components/player_test.h"
#include "engine_debug/logger.h"

void Player::Update()
{
	Chiffre++;
	Logger::Debug("test {}", Chiffre);
}
