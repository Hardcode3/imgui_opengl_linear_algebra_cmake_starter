#include <keyboard.h>

// initialize key callbacks list
std::vector<void(*)(GLFWwindow* window, int key, int scanCode, int action, int mods)> Keyboard::keyCallbacks_;

bool Keyboard::keys_[GLFW_KEY_LAST] = {0};
bool Keyboard::keysChanged_[GLFW_KEY_LAST] = {0};

void Keyboard::keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods)
{
    if (action != GLFW_RELEASE)
    {
        if (!keys_[key])
            keys_[key] = true;
    }
    else
        keys_[key] = false;
    
    keysChanged_[key] = action != GLFW_REPEAT;
    
    for (void(*func)(GLFWwindow*, int, int, int, int): Keyboard::keyCallbacks_)
        func(window, key, scanCode, action, mods);
}

