#include <sstream>
#include "GL/glew.h"
#include <string>
#include <fstream>
#include <iostream>



struct parsedShader {
    std::string vertex;
    std::string fragment;
};

static parsedShader parseShader(const std::string& filename) {

    std::ifstream stream(filename);

    enum class ShaderType {
        NONE = -1, FRAGMENT = 0, VERTEX = 1
    };

    std::stringstream ss[2];
    std::string line;
    ShaderType mode = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                mode = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                mode = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)mode] << line << "\n";
        }
    }
    return { ss[1].str(),ss[0].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "shader Compile error\n" << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}