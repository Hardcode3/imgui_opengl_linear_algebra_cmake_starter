message(STATUS "> Found tests/dependencies directory")

cmake_minimum_required(VERSION 3.10)

add_executable(imgui_test imgui_test.cpp)
target_link_libraries(imgui_test PUBLIC externals)
add_test(NAME imgui_test COMMAND imgui_test)

add_executable(eigen_test eigen_test.cpp)
target_link_libraries(eigen_test PUBLIC externals)
add_test(NAME eigen_test COMMAND eigen_test)

add_executable(glew_glfw_test glew_glfw_test.cpp)
target_link_libraries(glew_glfw_test PUBLIC externals libglew_static)
add_test(NAME glew_glfw_test COMMAND glew_glfw_test)

add_executable(glm_test glm_test.cpp)
target_link_libraries(glm_test PUBLIC externals)
add_test(NAME glm_test COMMAND glm_test)

add_executable(glfw_test glfw_test.cpp)
target_link_libraries(glfw_test PUBLIC externals)
add_test(NAME glfw_test COMMAND glfw_test)

set_property(TARGET imgui_test eigen_test glew_glfw_test glm_test glfw_test PROPERTY FOLDER "Tests/Dependencies")
