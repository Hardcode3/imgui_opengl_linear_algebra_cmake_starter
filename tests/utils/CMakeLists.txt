message(STATUS "> Found tests/utils directory")

cmake_minimum_required(VERSION 3.10)

add_executable(utils_str_test utils_str_test.cpp)
target_link_libraries(utils_str_test PUBLIC utils)
target_include_directories(utils_str_test PRIVATE $(PROJECT_SOURCE_DIR)/include/utils)
add_test(NAME utils_str_test COMMAND utils_str_test)

set_property(TARGET utils_str_test PROPERTY FOLDER "Tests/Utils")
