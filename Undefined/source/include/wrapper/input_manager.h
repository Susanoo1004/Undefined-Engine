#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "wrapper/service_type.h"
#include "wrapper/key_input.h"
#include "utils/flag.h"

class InputManager : public ServiceType
{
public:
	UNDEFINED_ENGINE InputManager();

	UNDEFINED_ENGINE void CreateKeyInput(std::string keyInputName, std::vector<int> keysToMonitor);

	UNDEFINED_ENGINE void SetInputMode(GLFWwindow* window, int mode, int value);

	UNDEFINED_ENGINE void SetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun callback);

	UNDEFINED_ENGINE std::shared_ptr<KeyInput> GetKeyInput(std::string keyInputName);

	std::unordered_map<std::string, std::shared_ptr<KeyInput>> KeyInputsMap;
};