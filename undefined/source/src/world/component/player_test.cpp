#include "world/component/player_test.h"
#include "logger/logger.h"

void Player::Update()
{
	Chiffre++;
	Logger::Debug("test {}", Chiffre);
}
