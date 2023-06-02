#ifndef MOUSE_H
#define MOUSE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

class Mouse
{
public:
    // casts to void pointers are done to suit glfw functions
    // define the list containing all the callbacks
    static std::vector<void(*)(GLFWwindow* window, double x, double y)> cursorPositionCallbacks_;
    static std::vector<void(*)(GLFWwindow* window, int button, int action, int mods)> mouseButtonCallbacks_;
    static std::vector<void(*)(GLFWwindow* window, double dx, double dy)> mouseWheelCallbacks_;
    
    // functions running the callbacks list
    static void cursorPositionCallback(GLFWwindow* window, double x, double y);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void mouseWheelCallback(GLFWwindow* window, double dx, double dy);
    
    static double getMousex() {return x_;}
    static double getMousey() {return y_;}
    static double getDx() {return dx_;}
    static double getDy() {return dy_;}
    static double getScrollDx() {return scrollDx_;}
    static double getScrollDy() {return scrollDy_;}
    
    static bool button(int button) {return buttons_[button];}
    static bool buttonChanged(int button);
    static bool mouseButtonUp(int button) {return !buttons_[button] && buttonChanged(button);}
    static bool mouseButtonDown(int button) {return !buttons_[button] && buttonChanged(button);}
    
private:
    static double x_, y_;
    static double lastx_, lasty_;
    static double dx_, dy_;
    static double scrollDx_, scrollDy_;
    static bool firstMouse_;
    static bool buttons_[];
    static bool buttonsChanged_[];
    
};

#endif /* end mouse.h */
