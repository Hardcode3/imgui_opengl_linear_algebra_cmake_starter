#ifndef APP_H
#define APP_H

#include <stdio.h>
#include "imgui_internal.h"
#include <app_base.h>
#include <glgraph.h>
#include <node_editor.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <csv.h>
#include <table_utils.h>
#include <printer.h>
#include <path.h>
#include <notification.h>
#include <imfilebrowser.h>


class App: public AppBase
{
public:
    App();
    App(int width, int height, char* windowTitle);
    ~App();
    void update() final;
    
private:
    virtual void main_menu_bar();

    void settings() final;
    void software_licence();
    void demos_w();
    void welcome_w();
    void perf_w();
    void cpu_gpu_usage();
    void framerate_info();
    void node_editor();
    void node_editor_menu_bar();
    void ray_tracer();
    void renderer();
    void load_csv();

    NodeEditor node_editor_;

    // demos
    bool show_imgui_demo_ = false;
    bool show_implot_demo_ = false;
    bool show_imnodes_demo_ = false;

    // windows
    bool show_welcom_w_ = false;
    bool show_perf_w_ = false;
    bool show_node_editor_ = true;
    bool show_settings_w_ = false;
    bool show_ray_tracer_w_ = false;
    bool show_renderer_w_ = false;
    bool show_csv_w_ = false;

    // legacy
    bool show_licence_w_ = false;

    // tabs
    bool show_style_t_ = true;
};

#endif // !APP_H
