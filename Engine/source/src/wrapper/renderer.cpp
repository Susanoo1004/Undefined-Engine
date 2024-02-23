#include "wrapper/renderer.h"

#include <iostream>

#include "logger/logger.h"

void Renderer::Init(float redBaseColor, float greenBaseColor, float blueBaseColor)
{
	gladLoadGL();
	glClearColor(redBaseColor, greenBaseColor, blueBaseColor, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::SetClearColor(GLbitfield)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::BindTexture(unsigned int ID)
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

unsigned int Renderer::SetShader(int shaderType, const char* vShaderCode)
{
    if (shaderType != GL_FRAGMENT_SHADER && shaderType != GL_VERTEX_SHADER)
    {
        return 0;
    }

    int success;
    char infoLog[512];

    // Shader
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &vShaderCode, NULL);
    glCompileShader(shader);
    // print compile errors if any
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        Logger::Error("{} COMPILATION_FAILED {}", ((shaderType == GL_FRAGMENT_SHADER) ? "FRAGMENT" : "VERTEX"), infoLog);
    };

    return shader;
}

void Renderer::UseShader(int ID)
{
	glUseProgram(ID);
}

void Renderer::UnUseShader()
{
	glUseProgram(0);
}

unsigned int Renderer::LinkShader(unsigned int ID, unsigned int vertex, unsigned int fragment)
{
    int success;
    char infoLog[512];

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        Logger::Error("SHADER_LINKING_FAILED {}", infoLog);
        return 0;
    }

    return ID;
}

void Renderer::SetBool(unsigned int ID, const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Renderer::SetInt(unsigned int ID, const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Renderer::SetFloat(unsigned int ID, const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Renderer::SetVec3(unsigned int ID, const std::string& name, Vector3 v) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &v.x);
}

void Renderer::SetMat4(unsigned int ID, const std::string& name, Matrix4x4 m) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, true, &m[0].x);
}

void Renderer::DeleteShader(unsigned int shader)
{
    glDeleteShader(shader);
}
