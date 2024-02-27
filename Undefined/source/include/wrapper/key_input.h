#pragma once

#include <glfw/glfw3.h>
#include <map>
#include <vector>

#include "utils/flag.h"

class KeyInput
{
public:
    UNDEFINED_ENGINE KeyInput(std::vector<int> keysToMonitor);
    UNDEFINED_ENGINE ~KeyInput();

    UNDEFINED_ENGINE bool GetIsKeyDown(int key);
    UNDEFINED_ENGINE bool GetIsEnabled();
    UNDEFINED_ENGINE void SetIsEnabled(bool value);

private:
    void SetIsKeyDown(int key, bool isDown);

    std::map<int, bool> KeysMap;
    bool IsEnabled;

public:
    UNDEFINED_ENGINE static void SetupKeyInputs();

private:
    UNDEFINED_ENGINE static void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    UNDEFINED_ENGINE static inline std::vector<KeyInput*> Instances;
};