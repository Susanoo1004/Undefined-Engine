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

    UNDEFINED_ENGINE const bool GetIsKeyDown(int key);
    UNDEFINED_ENGINE bool GetIsEnabled();
    UNDEFINED_ENGINE void SetIsEnabled(bool value);

    UNDEFINED_ENGINE void SetIsKeyDown(int key, bool isDown);
private:

    std::map<int, bool> mKeysMap;
    bool mIsEnabled;

private:
    friend class InputManager;
};
