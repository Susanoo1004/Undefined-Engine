#include "wrapper/renderer.h"

#include <iostream>

#include"resources/resource_manager.h"
#include"resources/texture.h"
#include"resources/model.h"

#include "engine_debug/logger.h"

void Renderer::Init()
{
	gladLoadGL();
	SetClearColor(0,0,0);
    EnableTest(GL_DEPTH_TEST);

    Debug.DebugInit();
}

void Renderer::SetClearColor(float redBaseColor, float greenBaseColor, float blueBaseColor)
{
    glClearColor(redBaseColor, greenBaseColor, blueBaseColor, 1.0f);
}

void Renderer::ClearBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::GenerateBuffer(int index, unsigned int* buffer)
{
    glGenBuffers(index, buffer);
}

void Renderer::GenerateVertexArray(int index, unsigned int* buffer)
{
    glGenVertexArrays(index, buffer);
}

void Renderer::GenTexture(unsigned int texNumber, unsigned int* ID)
{
    glGenTextures(texNumber, ID);
}

void Renderer::GenerateMipMap(unsigned int target)
{
    glGenerateMipmap(target);
}

void Renderer::ActiveTexture(unsigned int ID)
{
    glActiveTexture(ID);
}

void Renderer::BindTexture(unsigned int ID, unsigned int type)
{
	glBindTexture(type, ID);
}

void Renderer::BindTexture(int framebufferTarget, int attachement, unsigned int ID, int type)
{
    glFramebufferTexture2D(framebufferTarget, attachement, type, ID, 0);
}

void Renderer::BindFramebuffer(unsigned int target, unsigned int framebufferID)
{
    glBindFramebuffer(target, framebufferID);
}

void Renderer::BindRenderbuffer(unsigned int renderbufferID)
{
    glBindRenderbuffer(GL_RENDERBUFFER, renderbufferID);
}

void Renderer::BindBuffers(unsigned int VAO, unsigned int VBO, unsigned int EBO)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void Renderer::BindRenderbufferToFramebuffer(int framebufferTarget, int attachements, unsigned int renderbufferID)
{
	glFramebufferRenderbuffer(framebufferTarget, attachements, GL_RENDERBUFFER, renderbufferID);
}

void Renderer::AttributePointers(unsigned int index, int size, unsigned int type, int stride, const void* pointer, bool isNormalized)
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, isNormalized, stride, pointer);
}

void Renderer::SetBufferData(unsigned int target, int size, const void* data, unsigned int usage)
{
    glBufferData(target, size, data, usage);
}

void Renderer::SetRenderBufferStorageData(int format, float width, float height)
{
    glRenderbufferStorage(GL_RENDERBUFFER, format, (GLsizei)width, (GLsizei)height);
}

void Renderer::SetTextureParameteri(unsigned int target, unsigned int texParam, unsigned int texValue)
{
    glTexParameteri(target, texParam, texValue);
}

void Renderer::Draw(unsigned int mode, int size, unsigned int type, const void* indices)
{
    glDrawElements(mode, size, type, indices);
}

void Renderer::Draw(unsigned int mode, int start, int count)
{
    glDrawArrays(mode, start, count);
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

void Renderer::LinkShader(unsigned int &ID, unsigned int vertex, unsigned int fragment)
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
        return;
    }
}

void Renderer::SetUniform(unsigned int ID, const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Renderer::SetUniform(unsigned int ID, const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Renderer::SetUniform(unsigned int ID, const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Renderer::SetUniform(unsigned int ID, const std::string& name, const Vector3& v) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &v.x);
}

void Renderer::SetUniform(unsigned int ID, const std::string& name, const Matrix4x4& m) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, true, &m[0].x);
}

void Renderer::DeleteShader(unsigned int shader)
{
    glDeleteShader(shader);
}

void Renderer::DeleteFramebuffers(int number, unsigned int* framebuffersID)
{
    glDeleteFramebuffers(number, framebuffersID);
}

void Renderer::DeleteRenderbuffers(int number, unsigned int* renderbuffersID)
{
    glDeleteRenderbuffers(number, renderbuffersID);
}

void Renderer::DeleteTextures(int number, unsigned int* ID)
{
    glDeleteTextures(number, ID);
}

void Renderer::SetQuad(unsigned int VBO, unsigned int EBO, unsigned int VAO)
{
    float Vertices[] = {
        // positions          // normal           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int Indices[] =
    {  
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), &Vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), &Indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
