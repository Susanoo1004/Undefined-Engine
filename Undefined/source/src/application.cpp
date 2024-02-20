#include "application.h"

#include <glad/glad.h>
#include <iostream>

#include "singleton.h"
#include "resources/texture.h"
#include "resources/model.h"
#include "resources/resource_manager.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"
"layout (location = 2) in vec2 aTexCoord;\n"

"uniform mat4 model;\n"
"uniform mat4 vp;\n"

"out vec3 Normal;\n"
"out vec2 TexCoord;\n"
"out vec3 FragPos;\n"

"void main()\n"
"{\n"
"   FragPos = vec3(vp * model * vec4(aPos, 1.0f));\n"
"   Normal = aNormal;\n"
"   TexCoord = aTexCoord;\n"

"   gl_Position = vp * model * vec4(FragPos, 1.0);"
"}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"

"in vec2 TexCoord;\n"
"in vec3 Normal;\n"

"uniform sampler2D texture1;\n"

"void main()\n"
"{\n"
"   FragColor = texture(texture1, TexCoord);\n"
"}\n\0";


Application::Application() : cam(800,600)
{
}

void Application::Init()
{
    ResourceManager::resourceManager.Create<Texture>("assets/container.jpg");

    mVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(mVertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(mVertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(mVertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(mVertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(mFragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(mFragmentShader);
    // check for shader compile errors
    glGetShaderiv(mFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(mFragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, mVertexShader);
    glAttachShader(mShaderProgram, mFragmentShader);
    glLinkProgram(mShaderProgram);
    // check for linking errors
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(mShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragmentShader);

    if (mShaderProgram)
    {
        glUseProgram(mShaderProgram);
    }

    InitVikingRoom();
}

void Application::Update()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ResourceManager::resourceManager.Get<Texture>("assets/viking_room.png")->GetID());

    cam.ProcessInput(Singleton::windowManager->GetWindowVar());
    cam.Update();

    // modify the camera via the shader
    glUniformMatrix4fv(glGetUniformLocation(mShaderProgram, "vp"), 1, true, &cam.GetVP()[0].x);
    glUniformMatrix4fv(glGetUniformLocation(mShaderProgram, "model"), 1, true, &Matrix4x4::Identity()[0].x);
    
    glUseProgram(mShaderProgram);
    Draw();
}

void Application::InitQuad()
{
    float vertices[] = {
        // positions          // normal           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = 
    {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Application::InitVikingRoom()
{

    ResourceManager::resourceManager.Create<Texture>("assets/viking_room.png");

    ResourceManager::resourceManager.Create<Model>("assets/viking_room.obj");


    Model* model = ResourceManager::resourceManager.Get<Model>("assets/viking_room.obj");

    glGenBuffers(1, &mVBO);
    glGenVertexArrays(1, &mVAO);

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, model->vertexBuffer.size() * sizeof(Vertex),
        model->vertexBuffer.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureUV));
    glEnableVertexAttribArray(2);

}

void Application::Draw()
{
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, ResourceManager::resourceManager.Get<Model>("assets/viking_room.obj")->vertexBuffer.size());
}
