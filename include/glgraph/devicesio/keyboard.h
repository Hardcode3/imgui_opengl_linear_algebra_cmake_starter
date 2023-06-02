#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <vector>

class Keyboard
{
public:
    // list of the keyboard callback functions to be executed
    static std::vector<void(*)(GLFWwindow* window, int key, int scanCode, int action, int mods)> keyCallbacks_;
    
    static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
    
    static bool keyState(int key) {return keys_[key];}
    static bool keyChanged(int key) {return keysChanged_[key];}
    static bool keyUp(int key) {return !keys_[key] && keysChanged_[key];}
    static bool keyDown(int key) {return keys_[key] && keysChanged_[key];}
    static bool clearKeyChanged() {memset(keysChanged_, 0, (size_t)GLFW_KEY_LAST);}
    
private:
    static bool keys_[];
    static bool keysChanged_[];
    
};

#endif /* end keyboard.h */
