#include "scripts/player_behaviour.h"
#include "world/object.h"
#include "world/box_collider.h"
#include "camera/camera.h"

#include "wrapper/time.h"

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
	Vector3 right = Camera::CurrentCamera->Up.Cross(Camera::CurrentCamera->LookAt);

	float speed = 5.f;

	if (PlayerKeyInput->GetIsKeyDown(GLFW_KEY_W))
		GameTransform->Position += Vector3(Camera::CurrentCamera->LookAt.x, 0, Camera::CurrentCamera->LookAt.z) * Time::DeltaTime * speed;
	if (PlayerKeyInput->GetIsKeyDown(GLFW_KEY_S))
		GameTransform->Position -= Vector3(Camera::CurrentCamera->LookAt.x, 0, Camera::CurrentCamera->LookAt.z) * Time::DeltaTime * speed;
	if (PlayerKeyInput->GetIsKeyDown(GLFW_KEY_D))
		GameTransform->Position -= right * Time::DeltaTime * speed;
	if (PlayerKeyInput->GetIsKeyDown(GLFW_KEY_A))
		GameTransform->Position += right * Time::DeltaTime * speed;
	if (PlayerKeyInput->GetIsKeyDown(GLFW_KEY_SPACE))
		GameObject->GetComponent<BoxCollider>()->AddForce(Vector3(0, 20.0f, 0));
}
