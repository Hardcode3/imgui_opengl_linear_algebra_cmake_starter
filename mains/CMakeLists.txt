message(STATUS "> Found main directory")

add_executable (imgui_main "imgui_main.cpp")

target_link_libraries(imgui_main app imgui)

set_property(TARGET imgui_main PROPERTY FOLDER "Main")