#include "wrapper/input_manager.h"

#include <iostream>
#include <cassert>

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
}

void InputManager::SetInputMode(GLFWwindow* window, int mode, int value)
{
	glfwSetInputMode(window, mode, value);
}

void InputManager::SetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun callback)
{
	glfwSetCursorPosCallback(window, callback);
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
