message(STATUS "> Found tests/timer directory")

cmake_minimum_required(VERSION 3.10)

add_executable(timer_test timer_test.cpp)
target_link_libraries(timer_test PUBLIC timer raytracingkernel externals)
target_include_directories(timer_test PRIVATE $(PROJECT_SOURCE_DIR)/include/timer)
add_test(NAME timer_test COMMAND timer_test)

set_property(TARGET timer_test PROPERTY FOLDER "Tests/Timer")
