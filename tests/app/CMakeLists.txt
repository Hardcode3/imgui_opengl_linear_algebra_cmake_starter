message(STATUS "> Found tests directory")

cmake_minimum_required(VERSION 3.10)

add_executable(app_test app_test.cpp)
target_link_libraries(app_test PUBLIC app imgui)
add_test(NAME app_test COMMAND app_test)

set_property(TARGET app_test PROPERTY FOLDER "Tests/App")
