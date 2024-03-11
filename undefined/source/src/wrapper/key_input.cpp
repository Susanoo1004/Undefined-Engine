#include "wrapper/key_input.h"

#include <algorithm>

#include "service_locator.h"

KeyInput::KeyInput(std::vector<int> keysToMonitor) : mIsEnabled(true)
{
    for (int key : keysToMonitor)
    {
        mKeysMap[key] = false;
    }
    KeyInput::mInstances.push_back(this);
}

KeyInput::~KeyInput()
{
    mInstances.erase(std::remove(mInstances.begin(), mInstances.end(), this), mInstances.end());
}

bool KeyInput::GetIsKeyDown(int key)
{
    bool result = false;

    if (mIsEnabled)
    {
        std::map<int, bool>::iterator it = mKeysMap.find(key);

        if (it != mKeysMap.end())
        {
            result = mKeysMap[key];
        }
    }

    return result;
}

bool KeyInput::GetIsEnabled()
{
    return mIsEnabled;
}

void KeyInput::SetIsEnabled(bool value)
{
    mIsEnabled = value;
}

void KeyInput::SetIsKeyDown(int key, bool isDown)
{
    std::map<int, bool>::iterator it = mKeysMap.find(key);

    if (it != mKeysMap.end())
    {
        mKeysMap[key] = isDown;
    }
}

void KeyInput::SetupKeyInputs()
{
    glfwSetKeyCallback(ServiceLocator::Get<Window>()->GetWindowVar(), KeyInput::Callback);
    glfwSetMouseButtonCallback(ServiceLocator::Get<Window>()->GetWindowVar(), KeyInput::MouseButtonCallback);
}

void KeyInput::Callback(GLFWwindow*, int key, int , int action, int )
{
    for (KeyInput* keyInput : mInstances)
    {
        keyInput->SetIsKeyDown(key, action != GLFW_RELEASE);
    }
}

void KeyInput::MouseButtonCallback(GLFWwindow*, int button, int action, int )
{
    for (KeyInput* keyInput : mInstances)
    {
        keyInput->SetIsKeyDown(button, action != GLFW_RELEASE);
    }
}
