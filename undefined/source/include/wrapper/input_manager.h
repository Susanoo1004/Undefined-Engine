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

	UNDEFINED_ENGINE void CreateKeyInput(const std::string& keyInputName, const std::vector<int>& keysToMonitor);

	UNDEFINED_ENGINE void DeleteKeyInput(const std::string& keyInputName);

	UNDEFINED_ENGINE void SetInputMode(GLFWwindow* window, int mode, int value);

	UNDEFINED_ENGINE std::shared_ptr<KeyInput> GetKeyInput(const std::string& keyInputName);

	std::unordered_map<std::string, std::shared_ptr<KeyInput>> KeyInputsMap;

public:
	UNDEFINED_ENGINE static void Callbacks();

private:
	UNDEFINED_ENGINE static void Callback(GLFWwindow* window, int key, int, int action, int);

	UNDEFINED_ENGINE static void MouseButtonCallback(GLFWwindow*, int button, int action, int);

	UNDEFINED_ENGINE static inline std::vector<std::shared_ptr<KeyInput>> mInstances;
};