#include "app.h"


App::App():AppBase() {;}

App::App(int width, int height, char* windowTitle): AppBase(width, height, windowTitle) {;}

App::~App() {;}

void App::settings()
{
    static const char* style_items[] = { "Dark", "Light"};
    static int current_style_item = 0;
    if (show_settings_w_)
    {
        ImGui::Begin("Settings", &show_settings_w_);
        if (ImGui::BeginTabBar("Settings...", ImGuiTabBarFlags_Reorderable))
        {
            if (ImGui::BeginTabItem("Style"))
            {
                ImGui::Separator();
                if (ImGui::BeginTabBar("Editor"))
                {
                    if (ImGui::BeginTabItem("Simple editor"))
                    {
                        font_editor("Font");
                        style_selector();
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Full editor"))
                    {
                        ImGui::ShowStyleEditor();
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Solver"))
            {
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Ray tracing"))
            {
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Help"))
            {
                if (ImGui::CollapsingHeader("For developers"))
                {
                    ImGui::Text("PROGRAMMER GUIDE:");
                    ImGui::BulletText("Please see the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
                    ImGui::BulletText("Please see the comments in imgui.cpp.");
                    ImGui::BulletText("Please see the examples/ application.");
                    ImGui::BulletText("Enable 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.");
                    ImGui::BulletText("Enable 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.");
                    ImGui::Separator();
                    ImGui::Text("USER GUIDE:");
                    ImGui::ShowUserGuide();
                }
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::End();
    }
}

void App::software_licence()
{
    if (show_licence_w_)
    {
        ImGui::SetNextWindowSize(ImVec2(400, 200));
        ImGui::Begin("SpotSoft Licence", &show_licence_w_, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
        ImGui::Text("This software is strictly confidential to SpotLight.");

        ImGui::Separator();

        ImGui::Text("Visit SpotLight's website:");
        if (ImGui::Button("https://spotlight-earth.com/", ImVec2(-1, 0)))
        {
            // Open the website in a browser
            system("start https://spotlight-earth.com/");
        }

        ImGui::End();
    }
}

void App::update()
{
    main_menu_bar();
    software_licence();
    demos_w();
    welcome_w();
    perf_w();
    node_editor();
    settings();
    ray_tracer();
    renderer();
    load_csv();
    notif_sys.update(io_);
    file_browser_.Display();
}

void App::main_menu_bar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::BeginMenu("New workflow"))
            {
                if (ImGui::MenuItem("Node editor"))
                {
                    show_node_editor_ = true;
                }
                if(ImGui::MenuItem("Ray tracing"))
            	{
                	show_ray_tracer_w_ = true;
            	}
            	if(ImGui::BeginMenu("Demigration"))
            	{
            	    if(ImGui::MenuItem("Depth"))
            	    {
                	;
            	    }
               	    if(ImGui::MenuItem("Time"))
            	    {
                	;
            	    }
            	    ImGui::EndMenu();
            	}
            	ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Load"))
            {
                if (ImGui::MenuItem("CSV"))
                    show_csv_w_ = true;
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save"))
            {
                ;
            }
            if (ImGui::MenuItem("Close"))
            {
                close();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Copy"))
            {
                ;
            }
            if (ImGui::MenuItem("Cut"))
            {
                ;
            }
            if (ImGui::MenuItem("Paste"))
            {
                ;
            }
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("Settings"))
        {
            show_settings_w_ = true;
        }
        if (ImGui::BeginMenu("Other"))
        {
            ImGui::Checkbox("Performance", &show_perf_w_);
            ImGui::Checkbox("Welcome", &show_welcom_w_);
            if (ImGui::BeginMenu("Demos"))
            {
                ImGui::Checkbox("ImGui", &show_imgui_demo_);
                ImGui::Checkbox("ImPlot", &show_implot_demo_);

                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("Licence"))
            show_licence_w_ = true;

        ImGui::EndMainMenuBar();
    }
}

void App::demos_w()
{
    if (show_imgui_demo_)
        ImGui::ShowDemoWindow();
    if (show_implot_demo_)
        ImPlot::ShowDemoWindow();

}

void App::welcome_w()
{
    if (show_welcom_w_)
    {
        ImGui::Begin("Welcome to the Ray Tracing app !", &show_welcom_w_, ImGuiWindowFlags_MenuBar);
        ImGui::Text("The ray tracing application is meant to trace seismic rays based on a complex mathematical background.");
        ImGui::Text("Click here to start the workflow from scratch:");
        if (ImGui::Button("Start"))
            show_welcom_w_ = false;
        ImGui::End();
    }
}

void App::cpu_gpu_usage()
{
    ImGui::Text("CPU Usage: %.2f%%", 10);
    ImGui::Text("GPU Usage: %.2f%%", 20);

    static float cpu_values[1000];
    static float gpu_values[1000];
    static int values_offset = 0;
    static double last_time = glfwGetTime();

    double current_time = glfwGetTime();
    double delta_time = current_time - last_time;
    last_time = current_time;

    // Get CPU and GPU usage values using your preferred method
    float cpu_usage = 10;
    float gpu_usage = 20;

    cpu_values[values_offset] = cpu_usage;
    gpu_values[values_offset] = gpu_usage;
    values_offset = (values_offset + 1) % 1000;

    float x_min = values_offset - 1000;
    float x_max = values_offset;

    ImPlot::SetNextAxesLimits(x_min, x_max, 0, 100, ImGuiCond_Always);
    if (ImPlot::BeginPlot("CPU and GPU Usage", "Time (s)", "Usage (%)", ImVec2(-1, 0), ImPlotFlags_NoChild | ImPlotFlags_NoMenus | ImPlotFlags_NoBoxSelect, ImPlotAxisFlags_NoInitialFit)) {
        ImPlot::PlotLine("CPU Usage", cpu_values, 1000, values_offset, NULL, 0.0f, 100.0f);
        ImPlot::PlotLine("GPU Usage", gpu_values, 1000, values_offset, NULL, 0.0f, 100.0f);
        ImPlot::EndPlot();
    }
}

void App::framerate_info()
{
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    static float values[1000];
    static int values_offset = 0;
    static double last_time = glfwGetTime();

    double current_time = glfwGetTime();
    double delta_time = current_time - last_time;
    last_time = current_time;

    float fps = 1.0f / delta_time;
    values[values_offset] = fps;
    values_offset = (values_offset + 1) % 1000;

    float x_min = values_offset - 1000;
    float x_max = values_offset;

    ImPlot::SetNextAxesLimits(x_min, x_max, 0, 100, ImGuiCond_Always);
    if (ImPlot::BeginPlot("Framerate", "Time (s)", "Framerate (fps)", ImVec2(-1, 0), ImPlotFlags_NoChild | ImPlotFlags_NoMenus | ImPlotFlags_NoBoxSelect, ImPlotAxisFlags_NoInitialFit)) {
        ImPlot::PlotLine("Framerate", values, 1000, values_offset, NULL, 0.0f, 100.0f);
        ImPlot::EndPlot();
    }
}

void App::perf_w()
{
    if (show_perf_w_)
    {
        ImGui::Begin("Performances", &show_perf_w_, ImGuiWindowFlags_MenuBar);

        framerate_info();
        cpu_gpu_usage();

        ImGui::End();
    }
}

void App::node_editor()
{
    if (show_node_editor_)
    {
        ImGui::Begin("Node editor", &show_node_editor_,ImGuiWindowFlags_MenuBar);
        
        node_editor_.render();

        ImGui::End();
    }
}

void App::node_editor_menu_bar()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::Button("Check node layout")) { ; }
        if (ImGui::Button("Run ray tracing")) { ; }

        if (ImGui::Button("Close"))
            show_node_editor_ = false;
        ImGui::EndMenuBar();
    }
}

void App::ray_tracer()
{
    if(show_ray_tracer_w_)
    {
    	static bool synthetic_rt = true;
    	static bool isotropy_rt = true;
    	static bool stop_at_surface = true;
    	static bool paraxial_rt = false;
    	static bool use_interfaces = false;
    	static bool log = false;
    	static float sampling = 1e-3;
    	static float end_time = 2.0f;
    	static float alpha_shooting_angle = 0.0f;
    	static float theta_shooting_angle = 0.9f * M_PI;
        ImGui::Begin("Ray tracer workflow", &show_ray_tracer_w_, ImGuiWindowFlags_MenuBar);
        ImGui::Text("First chose the presets associated to the ray tracing algorithm:");
        
        ImGui::Separator();
        ImGui::BulletText("Choose booleans cooresponding to your ray:");
        ImGui::Checkbox("Work with synthetic models", &synthetic_rt);
        ImGui::Checkbox("Work with isotropy", &isotropy_rt);
        ImGui::Checkbox("Stop the ray at the surface", &stop_at_surface);
        ImGui::Checkbox("Use paraxial ray tracing", &paraxial_rt);
        ImGui::Checkbox("Use geological interfaces", &use_interfaces);
        ImGui::Checkbox("Log algorithm during processing", &log);
        
        ImGui::Separator();
        ImGui::BulletText("Parametrize time variables:");
        ImGui::SliderFloat("Solver sampling", &sampling, 1e-8, 1e-1);
        ImGui::SliderFloat("End time", &end_time, sampling, 20.0f);
        
        ImGui::Separator();
        ImGui::BulletText("Choose the shooting angles for the ray:");
        ImGui::SliderFloat("Alpha", &alpha_shooting_angle, 0, 2 * M_PI);
        ImGui::SliderFloat("Theta", &theta_shooting_angle, M_PI / 2, 3 * M_PI / 2);
        
        ImGui::Separator();
        ImGui::BulletText("Choose source's position:");
        
        ImGui::Separator();
        ImGui::BulletText("Configure the velocity model:");
        
        if(!isotropy_rt)
        {
            ImGui::Separator();
            ImGui::BulletText("Configure anisotropy epsilon model:");
        
            ImGui::Separator();
            ImGui::BulletText("Configure anisotropy delta model:");
        }
        
        if(use_interfaces)
        {
            ImGui::Separator();
            ImGui::BulletText("Configure geological interface:");
            if(ImGui::Button("Add"))
            {
            	;
            }
        }
        
        if(ImGui::Button("Trace the rays !"))
        {
	    ;
	}
        
        ImGui::End();
    }
}

void App::renderer()
{
    if (show_renderer_w_)
    {
        static std::vector<glm::vec3> points = { glm::vec3(2.f, 2.f, 2.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 0.0f, -4.0f) };
        
        ImGui::Begin("Render Points", &show_renderer_w_);

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
        ImVec2 canvas_size = ImGui::GetContentRegionAvail();
        const float radius = 3.f;
        for (const auto& point : points) {
            ImVec2 pos = ImVec2(canvas_pos.x + canvas_size.x * 0.5f + point.x * radius, canvas_pos.y + canvas_size.y * 0.5f - point.y * radius);
            draw_list->AddCircleFilled(pos, radius, IM_COL32(255, 0, 0, 255));
        }

        ImGui::End();
    }
}

void App::load_csv()
{
    if (show_csv_w_)
    {
        static bool show_table_win = false;
        static std::string csv_file_path = "None";
        static bool extract_header = true;
        static int radio_separator_selected = 0;
        static const char* radio_separator_labels[] = { ",", ";", ".", "space" };
        static int radio_separator_count = sizeof(radio_separator_labels) / sizeof(char*);
        static std::vector<std::string> type_filter = {".csv"};
        static std::vector<std::string> header;
        static std::vector<std::vector<float>> data;

        ImGui::Begin("Open CSV", &show_csv_w_, ImGuiWindowFlags_NoCollapse);

        ImGui::BulletText("Set the CSV path:");
        
        if (ImGui::Button("Search for files", ImVec2(-1, 25)))
        {
            file_browser_.SetTitle("Select a CSV file to visualize");
            file_browser_.SetTypeFilters(type_filter);
            file_browser_.Open();
        }

        ImGui::BulletText("Select the type of separator:");
        for (int i = 0; i < radio_separator_count; i++)
        {
            ImGui::SameLine();
            ImGui::RadioButton(radio_separator_labels[i], &radio_separator_selected, i);
        }

        ImGui::Checkbox("Extract csv file header:", &extract_header);

        if (file_browser_.HasSelected())
        {
            csv_file_path = file_browser_.GetSelected().string();
        }

        const char* file_path = csv_file_path.c_str();
        std::cout << file_path << std::endl;

        //ImGui::InputText("##input", file_path, sizeof(file_path));

        if (ImGui::Button("Load", ImVec2(-1, 50)))
        {
            data.clear();
            header.clear();
            if (!Utils::Path::file_exists(file_path))
            {
                notif_sys.insert_notification("The path of the CSV file is not recognized, consider checking it\n", ImVec4(1, 0, 0, 1), 4000);
                std::cout << "The path of the CSV file is not recognized, consider checking it\n";
                ImGui::End();
                return;
            }

            CSV csv_reader(file_path);
            Utils::Printer::print(data);
            if (csv_reader.read(data, header))
            {
                show_table_win = true;
            }
            
        }

        if (show_table_win)
        {
            Utils::Gui::display_table("CSV", &show_table_win, data, header);
        }
        ImGui::End();
    }
}