#include "player_behaviour.h"

PlayerBehaviour::PlayerBehaviour()
{
	std::vector<int> playerKeys = { GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_SPACE };
	InputManager* i = ServiceLocator::Get<InputManager>();

	i->CreateKeyInput("PlayerKeyInput", playerKeys);
	PlayerKeyInput = i->GetKeyInput("PlayerKeyInput");
}

PlayerBehaviour::~PlayerBehaviour()
{
}

void PlayerBehaviour::Update()
{
	if (PlayerKeyInput->GetIsKeyDown(GLFW_KEY_W))
		GameTransform->Position += Vector3(0, 0, 1);
}
