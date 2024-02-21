#include "resources/shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <toolbox/Vector3.h>

#include "singleton.h"
#include "logger/logger.h"

Shader::Shader()
{
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    Load(vertexPath, fragmentPath);
}

void Shader::Use()
{
    Singleton::renderer->UseShader(ID);
}

void Shader::UnUse()
{
    Singleton::renderer->UnUseShader();
}

unsigned int Shader::SetVertexShader(unsigned int vertex, const char* vShaderCode)
{
    vertex = Singleton::renderer->SetShader(GL_VERTEX_SHADER, vShaderCode);

    return vertex;
}

unsigned int Shader::SetFragmentShader(unsigned int fragment, const char* fShaderCode)
{
    fragment = Singleton::renderer->SetShader(GL_FRAGMENT_SHADER, fShaderCode);

    return fragment;
}

void Shader::Link(unsigned int vertex, unsigned int fragment)
{
    ID = Singleton::renderer->LinkShader(ID, vertex, fragment);
}

void Shader::SetBool(const std::string& name, bool value) const
{
    Singleton::renderer->SetBool(ID, name.c_str(), value);
}
void Shader::SetInt(const std::string& name, int value) const
{
    Singleton::renderer->SetInt(ID, name.c_str(), value);
}
void Shader::SetFloat(const std::string& name, float value) const
{
    Singleton::renderer->SetFloat(ID, name.c_str(), value);
}
void Shader::SetVec3(const std::string& name, Vector3 v) const
{
    Singleton::renderer->SetVec3(ID, name.c_str(), v);
}
void Shader::SetMat4(const std::string& name, Matrix4x4 m) const
{
    Singleton::renderer->SetMat4(ID, name.c_str(), m);
}

void Shader::Load(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        Logger::Error("SHADER::FILE_NOT_SUCCESFULLY_READ");
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    unsigned int vertex = 0;
    unsigned int fragment = 0;

    // vertex Shader
    vertex = SetVertexShader(vertex, vShaderCode);

    // fragment Shader
    fragment = SetFragmentShader(fragment, fShaderCode);

    // Link shaders
    Link(vertex, fragment);

    // delete the shaders as they're linked into our program now and no longer necessary
    Singleton::renderer->DeleteShader(vertex);
    Singleton::renderer->DeleteShader(fragment);
}
