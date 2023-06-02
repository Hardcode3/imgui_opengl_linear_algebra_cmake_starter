message(STATUS "> Found sources directory")

set(CMAKE_FOLDER sources)

add_subdirectory(timer)
add_subdirectory(glgraph)
add_subdirectory(app)
add_subdirectory(fstreamlib)
add_subdirectory(utils)
