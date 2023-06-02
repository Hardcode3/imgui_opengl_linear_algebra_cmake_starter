#include <mouse.h>
#include <camera.h>

// initialize mouse callbacks list
static std::vector<void(*)(GLFWwindow* window, double x, double y)> cursorPositionCallbacks_;
static std::vector<void(*)(GLFWwindow* window, int button, int action, int mods)> mouseButtonCallbacks_;
static std::vector<void(*)(GLFWwindow* window, double dx, double dy)> mouseWheelCallbacks_;

double Mouse::x_ = 0;
double Mouse::y_ = 0;

double Mouse::lastx_ = 0;
double Mouse::lasty_ = 0;

double Mouse::dx_ = 0;
double Mouse::dy_ = 0;

double Mouse::scrollDx_ = 0;
double Mouse::scrollDy_ = 0;

bool Mouse::firstMouse_ = true;

bool Mouse::buttons_[GLFW_MOUSE_BUTTON_LAST] = {0};

bool Mouse::buttonsChanged_[GLFW_MOUSE_BUTTON_LAST] = {0};

void Mouse::cursorPositionCallback(GLFWwindow *window, double x, double y)
{
    x_ = x;
    y_ = y;
    
    if (firstMouse_)
    {
        lastx_ = x;
        lasty_ = y;
        firstMouse_ = false;
    }
    
    dx_ = x_ - lastx_;
    // cordinates are inverted for y pos
    dy_ = lasty_ - y_;
    lastx_ = x_;
    lasty_ = dy_;
    
    for (void(*func) (GLFWwindow*, double, double): cursorPositionCallbacks_)
        func(window, x_, y_);
}

void Mouse::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    if (action != GLFW_RELEASE)
    {
        if(!buttons_[button])
        {
            buttons_[button] = true;
        }
    }
    else
        buttons_[button] = false;
    
        
    buttonsChanged_[button] = action != GLFW_REPEAT;
    
    for (void(*func)(GLFWwindow*, int, int, int) : mouseButtonCallbacks_)
        func(window, button, action, mods);
}

void Mouse::mouseWheelCallback(GLFWwindow *window, double dx, double dy)
{
    scrollDx_ = dx;
    scrollDy_ = dy_;
    
    for (void(*func)(GLFWwindow*, double, double): mouseWheelCallbacks_)
        func(window, dx, dy);
}

bool Mouse::buttonChanged(int button)
{
    bool result = buttonsChanged_[button];
    buttonsChanged_[button] = false;
    return result;
}
