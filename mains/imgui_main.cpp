#include <app.h>

int main(int, char**)
{
    App* app = new App(1920, 1080, (char*)"RayTracer");
    app->set_light_style();
    app->loop();
    delete app;
    return 0;
}

