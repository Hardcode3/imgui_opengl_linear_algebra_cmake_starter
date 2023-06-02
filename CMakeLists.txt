cmake_minimum_required(VERSION 2.8.12...3.24)

include("${CMAKE_SOURCE_DIR}/cmake/display_system_informations.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/display_project_informations.cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(
    "PROJECT" 
    VERSION 1.0
    DESCRIPTION "A template project"
    HOMEPAGE_URL "")

configure_file(cmake/PROJECTConfigure.h.in PROJECTConfigure.h)

# internal targets
option(PROJECT_WITH_EXECUTABLES "Compile main executables" ON)
option(PROJECT_WITH_TESTS "Compile tests" ON)
option(PROJECT_BUILD_DOC "Build documentation" ON)

# external dependencies
option(PROJECT_CLONE_GLEW "Initialize glew from remote repository as git submodule" ON)
option(PROJECT_CLONE_GLFW "Initialize glfw from remote repository as git submodule" ON)
option(PROJECT_CLONE_GLM "Initialize glm from remote repository as git submodule" ON)
option(PROJECT_CLONE_EIGEN "Initialize Eigen3 from remote repository as git submodule" ON)
option(PROJECT_CLONE_IMGUI "Initialize imgui from remote repository as git submodule" ON)

display_system_informations()
display_project_informations()

add_subdirectory(external)
add_subdirectory(src)

if (PROJECT_WITH_EXECUTABLES)
    add_subdirectory (mains)
endif ()

if (PROJECT_WITH_TESTS)
    enable_testing ()
    add_subdirectory (tests)
endif ()

if (PROJECT_BUILD_DOC)
    add_subdirectory(doc)
endif()

# Include CPack
include(CPack)

# Set some CPack options
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "PROJECT_COMPANY")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "PROJECT Installer")
set(CPACK_RESOURCE_FILE_LICENSE "LICENSE.md")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_GENERATOR "NSIS")
