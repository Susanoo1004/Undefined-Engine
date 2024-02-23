#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "wrapper/service_type.h"
#include "wrapper/key_input.h"

class InputManager : public ServiceType
{
public:
	InputManager();

	void CreateKeyInput(std::string keyInputName, std::vector<int> keysToMonitor);

	void SetInputMode(GLFWwindow* window, int mode, int value);

	void SetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun callback);

	std::shared_ptr<KeyInput> GetKeyInput(std::string keyInputName);

	std::unordered_map<std::string, std::shared_ptr<KeyInput>> KeyInputsMap;
};