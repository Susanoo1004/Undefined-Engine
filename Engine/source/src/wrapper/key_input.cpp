#include "wrapper/key_input.h"

#include <algorithm>

#include "service_locator.h"

KeyInput::KeyInput(std::vector<int> keysToMonitor) : IsEnabled(true) 
{
    for (int key : keysToMonitor) 
    {
        KeysMap[key] = false;
    }
    KeyInput::Instances.push_back(this);
}

KeyInput::~KeyInput() 
{
    Instances.erase(std::remove(Instances.begin(), Instances.end(), this), Instances.end());
}

bool KeyInput::GetIsKeyDown(int key) 
{
    bool result = false;

    if (IsEnabled) 
    {
        std::map<int, bool>::iterator it = KeysMap.find(key);

        if (it != KeysMap.end()) 
        {
            result = KeysMap[key];
        }
    }

    return result;
}

bool KeyInput::GetIsEnabled()
{
    return IsEnabled;
}

void KeyInput::SetIsEnabled(bool value)
{
    IsEnabled = value;
}

void KeyInput::SetIsKeyDown(int key, bool isDown) 
{
    std::map<int, bool>::iterator it = KeysMap.find(key);

    if (it != KeysMap.end()) 
    {
        KeysMap[key] = isDown;
    }
}

void KeyInput::SetupKeyInputs() 
{
    glfwSetKeyCallback(ServiceLocator::Get<WindowManager>()->GetWindowVar(), KeyInput::Callback);
}

void KeyInput::Callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    for (KeyInput* keyInput : Instances) 
    {
        keyInput->SetIsKeyDown(key, action != GLFW_RELEASE);
    }
}