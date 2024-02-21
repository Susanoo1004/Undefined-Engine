#include "application.h"

#include <glad/glad.h>
#include <iostream>

#include "singleton.h"
#include "resources/texture.h"
#include "resources/model.h"
#include "resources/resource_manager.h"

Application::Application() : cam(800,600)
{
}

void Application::Init()
{
    baseShader = Shader("source/shader_code/base_shader.vs", "source/shader_code/base_shader.fs");

    ResourceManager::resourceManager.Create<Texture>("assets/container.jpg");

    if (baseShader.ID)
    {
        baseShader.Use();
    }

    InitVikingRoom();
}

void Application::Update()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ResourceManager::resourceManager.Get<Texture>("viking_room.png")->GetID());

    cam.ProcessInput(Singleton::windowManager->GetWindowVar());
    cam.Update();

    // modify the camera in the shader
    baseShader.Use();
    baseShader.SetMat4("vp", cam.GetVP());
    baseShader.SetMat4("model", Matrix4x4::Identity());

    baseShader.Use();
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
    ResourceManager::resourceManager.Create<Texture>("viking_room.png", "assets/viking_room.png");

    ResourceManager::resourceManager.Create<Model>("viking_room.obj", "assets/viking_room.obj");

    std::shared_ptr<Model> model = ResourceManager::resourceManager.Get<Model>("viking_room.obj");

    glGenBuffers(1, &mVBO);
    glGenVertexArrays(1, &mVAO);

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (model->vertexBuffer.size() * sizeof(Vertex)),
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
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)ResourceManager::resourceManager.Get<Model>("viking_room.obj")->vertexBuffer.size());
}
