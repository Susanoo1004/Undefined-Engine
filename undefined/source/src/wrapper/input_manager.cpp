#include "wrapper/input_manager.h"

#include <iostream>
#include <cassert>

#include "service_locator.h"

InputManager::InputManager()
{
}

void InputManager::CreateKeyInput(std::string keyInputName, std::vector<int> keysToMonitor)
{
	std::shared_ptr<KeyInput> keyInput = std::make_shared<KeyInput>(keysToMonitor);

	auto&& p = KeyInputsMap.try_emplace(keyInputName, keyInput);

	if (!p.second)
	{
		p.first->second->~KeyInput();
		keyInput = std::make_shared<KeyInput>(keysToMonitor);
	}

	KeyInputsMap.emplace(keyInputName, keyInput);
	mInstances.push_back(keyInput);
}

UNDEFINED_ENGINE void InputManager::DeleteKeyInput(std::string keyInputName)
{
	mInstances.erase(std::remove(mInstances.begin(), mInstances.end(), GetKeyInput(keyInputName)), mInstances.end());
}

void InputManager::SetInputMode(GLFWwindow* window, int mode, int value)
{
	glfwSetInputMode(window, mode, value);
}

std::shared_ptr<KeyInput> InputManager::GetKeyInput(std::string keyInputName)
{
	auto&& p = KeyInputsMap.find(keyInputName);

	if (p == KeyInputsMap.end())
	{
		std::cerr << "Key Input name incorrect : " << keyInputName << std::endl;
		assert(false);
		return nullptr;
	}

	return p->second;
}

void InputManager::InputManagerCallback()
{
	GLFWwindow* mWindowManager = ServiceLocator::Get<Window>()->GetWindowVar();
	glfwSetKeyCallback(mWindowManager, InputManager::Callback);
	glfwSetMouseButtonCallback(mWindowManager, InputManager::MouseButtonCallback);
	glfwSetCursorPosCallback(mWindowManager, Camera::MouseCallback);
}

void InputManager::Callback(GLFWwindow*, int key, int, int action, int)
{
	for (std::shared_ptr<KeyInput> keyInput : mInstances)
	{
		keyInput->SetIsKeyDown(key, action != GLFW_RELEASE);
	}
}

void InputManager::MouseButtonCallback(GLFWwindow*, int button, int action, int)
{
	for (std::shared_ptr<KeyInput> keyInput : mInstances)
	{
		keyInput->SetIsKeyDown(button, action != GLFW_RELEASE);
	}
}