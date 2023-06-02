#include <app.h>
#include <iostream>
#include <RayTracingConfigure.h>

int main(int, char**)
{
	std::cout << "Project source directory: " << RayTracing_SOURCE_DIR << std::endl;
    App* app = new App(1300, 800, (char*)"RayTracer");
    app->set_dark_style();
    app->loop();
    delete app;
    return 0;
}
