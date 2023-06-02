#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <sstream>
#include <iostream>

// define the following in order to use fopen_s and memcpy_s functions
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <wchar.h>

#include <stdlib.h>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// TODO verify implementation for shader.cpp

// adapted from https://github.com/michaelg29/glmathviz
class Shader
{
public:
    unsigned int programID_;
    static std::stringstream defaultHeader_;
    static std::string defaultDirectory_;
    
    Shader() {;}
    Shader(bool includeDefaultHeader, const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath = nullptr);
    
    // make generate function private since it is used in the constructor ?
    void generate(bool includeDefaultHeader, const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath = nullptr);
    void activate() {glUseProgram(programID_);}
    void clean() {glDeleteProgram(programID_);}
    
    void setBool(const std::string& name, bool value);
    void setInteger(const std::string& name, int value);
    void setFloat(const std::string& name, int value);
    void setFloat3(const std::string& name, float value1, float value2, float value3);
    void setFloat3(const std::string& name, glm::vec3 values);
    void setFloat4(const std::string& name, float value1, float value2, float value3, float value4);
    void setFloat4(const std::string& name, glm::vec4 values);
    void setMatrix3(const std::string& name, glm::mat3 matrix3);
    void setMatrix4(const std::string& name, glm::mat4 matrix4);
    
    static unsigned int compile(bool includeDefaultHeader, const char* path, unsigned int type);
    static void attach(unsigned int ID, unsigned int shaderID);
    static void loadDefaultHeader(const char* path);
    static void clearDefaultHeader();
    static char* loadShaderSource(bool includeDefaultHeader, const char* path);
    
    // error handling
    static int getCompilationErrorCode(unsigned int programID, const char* path);
    static int getLinkingErrorCode(unsigned int programID);
};

#endif /* end shader.h */
