#include <shader.h>

// static variables
std::stringstream Shader::defaultHeader_;


// non member function
void compilenattachh(unsigned int ID, bool includeDefaultHeader, const char* path, unsigned int type)
{
    if (!path)
        return;
    
    unsigned int shader = Shader::compile(includeDefaultHeader, path, type);
    
    glAttachShader(ID, shader);
    glDeleteShader(shader);
}


// member functions
Shader::Shader(bool includeDefaultHeader, const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath)
{
    generate(includeDefaultHeader, vertexShaderPath, geometryShaderPath);
}

int Shader::getCompilationErrorCode(unsigned int programID, const char* path)
{
    int success;
    unsigned int logSize = 512;
    glGetShaderiv(programID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char* infoLog = (char*)malloc(logSize);
        glGetShaderInfoLog(programID, logSize, NULL, infoLog);
        std::cout << "Error compiling shaders at " << path << "\n" << infoLog << "\n";
    }
    return success;
}


int Shader::getLinkingErrorCode(unsigned int programID)
{
    int success;
    unsigned int logSize = 512;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char* infoLog = (char*)malloc(logSize);
        glGetProgramInfoLog(programID, logSize, NULL, infoLog);
        std::cout << "Linking error \n " << infoLog << "\n";
    }
    return success;
}


void Shader::generate(bool includeDefaultHeader, const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath)
{
    programID_ = glCreateProgram();
    
    compilenattachh(programID_, includeDefaultHeader, vertexShaderPath, GL_VERTEX_SHADER);
    compilenattachh(programID_, includeDefaultHeader, fragmentShaderPath, GL_FRAGMENT_SHADER);
    compilenattachh(programID_, includeDefaultHeader, geometryShaderPath, GL_GEOMETRY_SHADER);
    
    glLinkProgram(programID_);
    
    getLinkingErrorCode(programID_);
}

unsigned int Shader::compile(bool includeDefaultHeader, const char *path, unsigned int type)
{
    unsigned int createdShader = glCreateShader(type);
    char* shader = loadShaderSource(includeDefaultHeader, path);
    glShaderSource(createdShader, 1, &shader, NULL);
    glCompileShader(createdShader);
    free(shader);
    
    return getCompilationErrorCode(createdShader, path);
}

void Shader::setBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(programID_, name.c_str()), (int)value);
}

void Shader::setInteger(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(programID_, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, int value)
{
    glUniform1f(glGetUniformLocation(programID_, name.c_str()), value);
}

void Shader::setFloat3(const std::string &name, float value1, float value2, float value3)
{
    glUniform3f(glGetUniformLocation(programID_, name.c_str()), value1, value2, value3);
}

void Shader::setFloat3(const std::string &name, glm::vec3 values)
{
    glUniform3f(glGetUniformLocation(programID_, name.c_str()), values.x, values.y, values.z);
}

void Shader::setFloat4(const std::string &name, float value1, float value2, float value3, float value4)
{
    glUniform4f(glGetUniformLocation(programID_, name.c_str()), value1, value2, value3, value4);
}

void Shader::setFloat4(const std::string &name, glm::vec4 values)
{
    glUniform4f(glGetUniformLocation(programID_, name.c_str()), values.x, values.y, values.z, values.w);
}

void Shader::setMatrix3(const std::string &name, glm::mat3 matrix3)
{
    glUniformMatrix3fv(glGetUniformLocation(programID_, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix3));
}

void Shader::setMatrix4(const std::string &name, glm::mat4 matrix4)
{
    glUniformMatrix4fv(glGetUniformLocation(programID_, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix4));
}


void Shader::loadDefaultHeader(const char *path)
{
    char* fileContent = Shader::loadShaderSource(false, path);
    Shader::defaultHeader_ << fileContent;
    free(fileContent);
}

void Shader::clearDefaultHeader()
{
    Shader::defaultHeader_.clear();
}

char* Shader::loadShaderSource(bool includeDefaultHeader, const char *path)
{
    std::string absolutPath = Shader::defaultDirectory_ + '/' + path;
    
    FILE* file = nullptr;
    //fopen_s(&file, absolutPath.c_str(), "rb");
    if(!file)
    {
        std::cout << "Can not open the following shader: " << absolutPath << "\n";
        return nullptr;
    }
    // cursor at the end of the file
    fseek(file, 0, SEEK_END);
    // get the length of the whole file
    long int length = ftell(file);
    // cursor at the beginning
    fseek(file, 0, SEEK_SET);
    
    char* res = nullptr;
    long int cursor = 0;
    if(includeDefaultHeader)
    {
        cursor = Shader::defaultHeader_.str().size();
        res = (char*)malloc(length + 1);
        //memcpy_s(res, cursor + length + 1, Shader::defaultHeader_.str().c_str(), cursor);
    }
    else
        res = (char*)malloc(length + 1);
    
    fread(res + cursor, 1, length, file);
    res[cursor + length] = 0;
    
    return res;
}
