message(STATUS "> Found external directory")

# glew configuration

if((NOT EXISTS glew) OR (NOT IS_DIRECTORY glew))
	message(STATUS "> Cloning glew from remote...")
	execute_process(
		COMMAND git submodule update --init glew
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
else()
	message(STATUS "> Found glew submodule folder")
endif()

add_subdirectory(glew)
set(glew-cmake_BUILD_SHARED OFF)
set_property(TARGET libglew_static PROPERTY FOLDER "External/GLEW_STATIC")
set_property(TARGET libglew_shared PROPERTY FOLDER "External/GLEW_SHARED")


# glfw configuration
if ((NOT EXISTS glfw) OR (NOT IS_DIRECTORY glfw))
	message(STATUS "> Cloning GLFW from remote...")
	execute_process(
		COMMAND git submodule update --init glfw
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
else()
	message(STATUS "> Found GLFW submodule folder")
endif()

# OpenGL configuration
# search for OpenGL on the system
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")
# add glfw subdirectory after having found OpenGL
add_subdirectory(glfw)
if(MSVC)
	SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()
set_property(TARGET glfw update_mappings  PROPERTY FOLDER "External/GLFW3")


# glm configuration
if ((NOT EXISTS glm) OR (NOT IS_DIRECTORY glm))
	message(STATUS "> Cloning glm from remote...")
	execute_process(
		COMMAND git submodule update --init glm
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
else()
	message(STATUS "> Found glm submodule folder")
endif()
add_subdirectory(glm)
set_property(TARGET glm uninstall PROPERTY FOLDER "External/GLM")



# Eigen3 configuration
if ((NOT EXISTS eigen) OR (NOT IS_DIRECTORY eigen))
	message(STATUS "> Cloning Eigen from remote...")
	execute_process(
		COMMAND git submodule update --init eigen
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
else()
	message(STATUS "> Found Eigen3 submodule folder")
endif()
set(EIGEN_BUILD_CMAKE_PACKAGE OFF)
set(EIGEN_BUILD_PKGCONFIG OFF)
set(EIGEN_SPLIT_LARGE_TESTS OFF)
set(EIGEN_BUILD_DOC OFF)
set(EIGEN_BUILD_CMAKE_PACKAGE OFF)
set(EIGEN_DOC_USE_MATHJAX OFF)
add_subdirectory(eigen)
set_property(TARGET eigen PROPERTY FOLDER "External/Eigen3")


# Imgui configuration
if ((NOT EXISTS imgui) OR (NOT IS_DIRECTORY imgui))
	message(STATUS "> Cloning imgui from remote...")
	execute_process(
		COMMAND git submodule update --init imgui
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
else()
	message(STATUS "> Found Imgui submodule folder")
endif()

set(target_name imgui)
set(imgui_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/imgui
	CACHE PATH "Imgui include directory")
set(imgui_DIR ${CMAKE_SOURCE_DIR}/external/imgui
	CACHE PATH "Imgui directory")
		
# setting up the target
add_library(${target_name} STATIC "")
target_link_libraries(${target_name} ${OPENGL_LIBRARIES} glfw libglew_static libglew_shared)

target_sources(${target_name}
	# cpp
	PRIVATE
		# GLFW
		"${PROJECT_SOURCE_DIR}/external/imgui/backends/imgui_impl_glfw.cpp"
		# OpenGL3
		"${PROJECT_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.cpp"

		# sources
		"${PROJECT_SOURCE_DIR}/external/imgui/imgui.cpp"
		"${PROJECT_SOURCE_DIR}/external/imgui/imgui_demo.cpp"
		"${PROJECT_SOURCE_DIR}/external/imgui/imgui_draw.cpp"
		"${PROJECT_SOURCE_DIR}/external/imgui/imgui_tables.cpp"
		"${PROJECT_SOURCE_DIR}/external/imgui/imgui_widgets.cpp"

		"${PROJECT_SOURCE_DIR}/external/implot/implot_demo.cpp"
		"${PROJECT_SOURCE_DIR}/external/implot/implot_items.cpp"
		"${PROJECT_SOURCE_DIR}/external/implot/implot.cpp"

		"${PROJECT_SOURCE_DIR}/external/imnodes/imnodes.cpp"

	# headers
	PRIVATE
		# GLFW
		"${PROJECT_SOURCE_DIR}/external/imgui/backends/imgui_impl_glfw.h"
		# OpenGL3
		"${PROJECT_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.h"
		"${PROJECT_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3_loader.h"

		# sources
		"${PROJECT_SOURCE_DIR}/external/imgui/imconfig.h"
		"${PROJECT_SOURCE_DIR}/external/imgui/imgui.h"
		"${PROJECT_SOURCE_DIR}/external/imgui/imgui_internal.h"
		"${PROJECT_SOURCE_DIR}/external/imgui/imstb_rectpack.h"
		"${PROJECT_SOURCE_DIR}/external/imgui/imstb_textedit.h"
		"${PROJECT_SOURCE_DIR}/external/imgui/imstb_truetype.h"

		"${PROJECT_SOURCE_DIR}/external/implot/implot.h"
		"${PROJECT_SOURCE_DIR}/external/implot/implot_internal.h"
		
		"${PROJECT_SOURCE_DIR}/external/imnodes/imnodes.h"
		"${PROJECT_SOURCE_DIR}/external/imnodes/imnodes_internal.h"
)

target_include_directories(${target_name}
	PUBLIC
		"${PROJECT_SOURCE_DIR}/external/imgui"
		"${PROJECT_SOURCE_DIR}/external/imgui/backends"
		"${PROJECT_SOURCE_DIR}/external/implot"
		"${PROJECT_SOURCE_DIR}/external/imnodes"
		"${PROJECT_SOURCE_DIR}/external/glew/include"
		"${PROJECT_SOURCE_DIR}/external/glew"
		"${PROJECT_SOURCE_DIR}/external/glm"
		"${PROJECT_BINARY_DIR}"
	)

# install the headers to make them available for the installed target
# install(DIRECTORY ${imgui_INCLUDE_DIR}/imgui DESTINATION ${CMAKE_BINARY_DIR}/external/imgui)

# export the target so it can be included using find_package
# install(TARGETS externals EXPORT imgui DESTINATION ${CMAKE_BINARY_DIR}/external/imgui)

set_property(TARGET imgui PROPERTY FOLDER "External/Imgui")
