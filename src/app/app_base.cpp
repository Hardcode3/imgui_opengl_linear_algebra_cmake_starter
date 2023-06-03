#include <app_base.h>

AppBase::AppBase()
{
    assert(init() == 0);
}

AppBase::AppBase(int width, int height, char *windowTitle) : width_(width), height_(height), windowTitle_(windowTitle)
{
    assert(init() == 0);
}

AppBase::~AppBase()
{
    destroy();
}

void AppBase::settings()
{
    style_->WindowRounding = 8.0f;
    style_->GrabRounding = 8.0f;
    style_->FrameRounding = 7.0f;
    style_->ScrollbarRounding = 12.0f;
    style_->WindowPadding = ImVec2(9.0f, 9.0f);
    style_->PopupRounding = 8.0f;
    style_->PopupBorderSize = 2.0f;
}

void AppBase::set_dark_style()
{
    if (is_light_style_)
    {
        set_background_color(ImVec4(0.45f, 0.55f, 0.60f, 1.00f));
        ImGui::StyleColorsDark();
    }
}

void AppBase::set_light_style()
{
    if (is_light_style_)
    {
        set_background_color(ImVec4(.9f, .9f, .9f, 1.0f));
        ImGui::StyleColorsLight();
    }
}

void AppBase::glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int AppBase::init()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    glsl_version_ = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    glsl_version_ = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
    // GL 3.0 + GLSL 130
    glsl_version_ = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    window_ = glfwCreateWindow(width_, height_, windowTitle_, NULL, NULL);
    if (window_ == NULL)
        return 1;
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1); // Enable vsync
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImNodes::CreateContext();

    io_ = &ImGui::GetIO();
    assert(io_ != nullptr);

    io_->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    if (is_light_style_)
        ImGui::StyleColorsLight();
    else
        ImGui::StyleColorsDark();
    // apply custom window settings here
    style_ = &ImGui::GetStyle();
    settings();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init(glsl_version_);

    // Handle high DPI scaling for retina displays
    glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) 
        {
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            ImGui::GetIO().DisplaySize = ImVec2((float)display_w, (float)display_h);
        });

    setup_fonts();
    
    // set the minimum and maximum sizes of the window
    glfwSetWindowSizeLimits(window_, 640, 480, GLFW_DONT_CARE, GLFW_DONT_CARE);

    return 0;
}

void AppBase::setup_fonts()
{
    io_->Fonts->AddFontDefault();
    assert(add_font("\\Roboto\\Roboto-Regular.ttf"));
    assert(add_font("\\Roboto\\Roboto-Light.ttf"));
    assert(add_font("\\Roboto\\Roboto-Bold.ttf"));
    assert(add_font("\\Roboto\\Roboto-Medium.ttf"));

    io_->FontDefault = io_->Fonts->Fonts[4];
}

bool AppBase::add_font(const char* relative_font_path)
{
    std::string font_path_str = Utils::Path::convert_to_c_path(PROJECT_FONTS_DIR);
    const char* font_path = const_cast<char*>(font_path_str.c_str());
    
    if ((font_path_str.size() + strlen(relative_font_path) > 200))
    {
        std::cout << "The path to the porject is too long for the path buffer, consider mooving your project as close to the root as possible." << std::endl;
        return false;
    }

    char font[200];
    Utils::Str::concatenate_cstr(font_path, relative_font_path, font);

    if (Utils::Path::file_exists(font))
    {
        for (int font_size : font_size_range_)
        {
            io_->Fonts->AddFontFromFileTTF(font, font_size);
        }
        return true;
    }
    return false;
}

void AppBase::loop()
{
    while (!glfwWindowShouldClose(window_))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        // call the newly written windows by overriding update using inheritance
        ImGui::DockSpaceOverViewport();
        update();

        // Rendering
        ImGui::Render();
        glfwGetFramebufferSize(window_, &width_, &height_);

        glViewport(0, 0, width_, height_);
        glClearColor(background_color_.x * background_color_.w, background_color_.y * background_color_.w, background_color_.z * background_color_.w, background_color_.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window_);
    }
}

void AppBase::close()
{
    glfwSetWindowShouldClose(window_, GLFW_TRUE);
}

void AppBase::destroy()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImNodes::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window_);
    glfwTerminate();
}

void AppBase::font_editor(const char *label)
{
    ImGuiIO &io = ImGui::GetIO();
    ImFont *font_current = ImGui::GetFont();
    if (ImGui::BeginCombo("Font", font_current->GetDebugName()))
    {
        for (int n = 0; n < io.Fonts->Fonts.Size; n++)
        {
            ImFont *font = io.Fonts->Fonts[n];
            ImGui::PushID((void *)font);
            if (ImGui::Selectable(font->GetDebugName(), font == font_current))
                io.FontDefault = font;
            ImGui::PopID();
        }
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    Utils::Gui::help_marker(
        "- Load additional fonts with io.Fonts->AddFontFromFileTTF().\n"
        "- The font atlas is built when calling io.Fonts->GetTexDataAsXXXX() or io.Fonts->Build().\n"
        "- Read FAQ and documentation in misc/fonts/ for more details.\n"
        "- If you need to add/remove fonts at runtime (e.g. for DPI change), do it before calling NewFrame().");
}

bool AppBase::style_selector()
{
    static int style_idx = 1;
    if (ImGui::Combo("Color scheme", &style_idx, "Classic\0Dark\0Light\0"))
    {
        switch (style_idx)
        {
        case 0:
            ImGui::StyleColorsClassic();
            break;
        case 1:
            ImGui::StyleColorsDark();
            break;
        case 2:
            ImGui::StyleColorsLight();
            break;
        }
        return true;
    }
    return false;
}

void AppBase::set_vsync(int swap_interval)
{
    // must be called after the creation of the opengl context
    if (swap_interval == 0 || swap_interval == 1)
        glfwSwapInterval(swap_interval);
}
