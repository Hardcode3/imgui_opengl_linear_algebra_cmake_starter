# Imgui - OpenGL - Linear algebra - CMake C++ template

![licence](https://img.shields.io/static/v1?label=Licence&message=MIT&color=yellow)
![os support](https://img.shields.io/static/v1?label=Supports&message=Windows|Linux|MacOS&color=blue)
![repo size](https://img.shields.io/github/repo-size/Hardcode3/Imgui-OpenGL-Linear-Algebra-starter)

A template project using [Imgui](external/imgui) as graphical user interface ([glfw](external/glfw), [glm](external/glm), [glew](external/glew) and [OpenGL](https://www.opengl.org/)), and [Eigen3](external/eigen) as linear algebra library.
For more details about the Apach 2.0 licence, visit [tldrlegal.com](https://tldrlegal.com/license/apache-license-2.0-(apache-2.0)).
For more details about the MIT licence, visit [tldrlegal.com](https://tldrlegal.com/license/mit-license)

## Dependencies

The code is build to run with the following libraries (included in the repository under [external](external/)):

- [OpenGL](https://www.opengl.org/) (specification)
- [GLEW](https://glew.sourceforge.net/) (included)
- [GLFW](https://www.glfw.org/) (included)
- [GLM](https://github.com/g-truc/glm) (included)
- [ImGui](https://github.com/ocornut/imgui) (included)
- [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) (included)

## Structure

An organized structure has been chosen for this template.

- [cmake](cmake) contains a configure file to get the minor and major versions of the current project.
- [external](external) code goes into external folder at the root of the project.
- [include](include) gather every self written header file.
- [mains](mains) contains the main executable i.e. cpp file that drives all the project.
- [src](src) gather every self written cpp file of the project.
- [tests](tests) uses CTests to use a test driven approach during the development of the project.

## Cloning

This repository contains submodules meaning that a recursive cloning can be done.
To clone this repository, make sure you have git installed and clone the project into the chosen folder using

```git bash
git clone --recursive https://github.com/Hardcode3/Imgui_with_eigen_cmake_template.git
```

If no recursive statement, cmake updated the module and clones it.

## Configuring and generating

The build steps has been tested and runs fine on:

- Microsoft Windows 10, 11
- MacOSX
- Linux Ubuntu

### Configuration steps on Linux

Configuration on Linux requires additional libraries:
If required, run the following commands to install needed libraries (detailed in the cmake configuration and building process):

```bash
sudo apt-get update -y
```

Install OpenGL if needed:

```bash
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

```bash
sudo apt-get install -y libxrandr-dev
```

```bash
sudo apt-get install -y libxinerama-dev
```

```bash
sudo apt-get install -y libxcursor-dev
```

```bash
sudo apt-get install -y libxi-dev
```

### Configuration steps on macOS

There is no additional configuration step on macOS.

### Configuration steps on Windows

There is no additional configuration step on Windows.

### General configuration & build process

Make sure you have CMake installed and inside the clone repo, type:

```bash cmd terminal
mkdir build
cd build
cmake ..
cmake --build .
```

Or use CMakeGui for this.
For more details, check [cmake.org](https://cmake.org/)

Generating the RUNTESTS executable (CTests) should output something like this if everything is well configured:

```text
1>    Start 1: imgui_test
1>1/4 Test #1: imgui_test .......................   Passed    0.67 sec
1>    Start 2: eigen_test
1>2/4 Test #2: eigen_test .......................   Passed    0.02 sec
1>    Start 3: glew_glfw_test
1>3/4 Test #3: glew_glfw_test ...................   Passed    0.65 sec
1>    Start 4: glm_test
1>4/4 Test #4: glm_test .........................   Passed    0.04 sec
1>
1>100% tests passed, 0 tests failed out of 4
1>
1>Total Test time (real) =   1.38 sec
```
