message(STATUS "> Found sources/glgraph directory")

set(CMAKE_FOLDER glgraph)
set(target_name glgraph)

add_library(${target_name} STATIC "")

target_link_libraries(${target_name} PRIVATE externals)

target_sources(${target_name}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/glgraph/glgraph.cpp"
	"${PROJECT_SOURCE_DIR}/src/glgraph/glgraph_demo.cpp"
	"${PROJECT_SOURCE_DIR}/src/glgraph/scatter3d.cpp"

	"${PROJECT_SOURCE_DIR}/src/glgraph/devicesio/camera.cpp"
	"${PROJECT_SOURCE_DIR}/src/glgraph/devicesio/keyboard.cpp"
	"${PROJECT_SOURCE_DIR}/src/glgraph/devicesio/mouse.cpp"

	"${PROJECT_SOURCE_DIR}/src/glgraph/rendering/material.cpp"
	"${PROJECT_SOURCE_DIR}/src/glgraph/rendering/shader.cpp"


    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/glgraph/glgraph.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/glgraph_demo.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/scatter3d.h"

	"${PROJECT_SOURCE_DIR}/include/glgraph/rendering/arrow.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/rendering/path.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/rendering/programs.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/rendering/rectangle.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/rendering/sphere.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/rendering/surface.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/rendering/material.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/rendering/surface.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/rendering/shader.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/rendering/transition.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/rendering/uniformmem.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/rendering/vertexmem.h"

	"${PROJECT_SOURCE_DIR}/include/glgraph/devicesio/camera.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/devicesio/keyboard.h"
	"${PROJECT_SOURCE_DIR}/include/glgraph/devicesio/mouse.h"
)

target_include_directories (${target_name}
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include/glgraph"
        "${PROJECT_SOURCE_DIR}/include/glgraph/rendering"
        "${PROJECT_SOURCE_DIR}/include/glgraph/devicesio"
	"${PROJECT_SOURCE_DIR}/src/glgraph/rendering/shaders"
        "${PROJECT_BINARY_DIR}"
)

set_property(TARGET ${target_name} PROPERTY FOLDER "Sources/glGraph")