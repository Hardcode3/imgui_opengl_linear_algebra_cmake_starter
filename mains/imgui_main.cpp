#include <app.h>

int main(int, char**)
{
    std::cout << "Project source directory: " << PROJECT_SOURCE_DIR << std::endl;
    App* app = new App(1300, 800, (char*)"PROJECT");
    app->set_dark_style();
    app->loop();
    delete app;
    return 0;
}

