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

	std::unordered_map<std::string, std::shared_ptr<KeyInput>> KeyInputsMap;

	void CreateKeyInput(std::string keyInputName, std::vector<int> keysToMonitor);

	std::shared_ptr<KeyInput> GetKeyInput(std::string keyInputName);
};