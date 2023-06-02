message(STATUS "> Found main directory")

add_executable (imgui_main "imgui_main.cpp")

target_link_libraries(imgui_main app externals)

set_property(TARGET imgui_main PROPERTY FOLDER "Mains")