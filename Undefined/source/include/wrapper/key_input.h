#pragma once

#include <glfw/glfw3.h>
#include <map>
#include <vector>

class KeyInput
{
public:
    KeyInput(std::vector<int> keysToMonitor);
    ~KeyInput();

    bool GetIsKeyDown(int key);
    bool GetIsEnabled();
    void SetIsEnabled(bool value);

private:
    void SetIsKeyDown(int key, bool isDown);

    std::map<int, bool> KeysMap;
    bool IsEnabled;

public:
    static void SetupKeyInputs();

private:
    static void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static inline std::vector<KeyInput*> Instances;
};