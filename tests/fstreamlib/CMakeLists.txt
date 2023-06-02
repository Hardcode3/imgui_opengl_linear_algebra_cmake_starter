message(STATUS "> Found tests/fstreamlib directory")

cmake_minimum_required(VERSION 3.10)

add_executable(csv_test csv_test.cpp)
target_link_libraries(csv_test PUBLIC fstreamlib utils)
add_test(NAME csv_test COMMAND csv_test)

set_property(TARGET csv_test PROPERTY FOLDER "Tests/fstreamlib")
