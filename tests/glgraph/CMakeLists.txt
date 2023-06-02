message(STATUS "> Found tests/glgraph directory")

set(CMAKE_FOLDER glgraphtests)

cmake_minimum_required(VERSION 3.10)

add_executable(glgraph_test glgraph_test.cpp)
target_link_libraries(glgraph_test PUBLIC externals glgraph)
target_include_directories(glgraph_test PRIVATE $(PROJECT_SOURCE_DIR)/include/glgraph)
add_test(NAME glgraph_test COMMAND glgraph_test)

add_executable(interactive_env_test interactive_env.cpp)
target_link_libraries(interactive_env_test PUBLIC externals glgraph)
target_include_directories(interactive_env_test PRIVATE $(PROJECT_SOURCE_DIR)/include/glgraph)
add_test(NAME interactive_env_test COMMAND interactive_env_test)

set_property(TARGET glgraph_test interactive_env_test PROPERTY FOLDER "Tests/glGraph")