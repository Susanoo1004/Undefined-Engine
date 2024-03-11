#include "application.h"

#include <glad/glad.h>
#include <iostream>

#include "service_locator.h"

#include "resources/texture.h"
#include "resources/model.h"
#include "resources/resource_manager.h"

#include "interface/interface.h"

Application::Application()
{
}

void Application::Init()
{
    ResourceManager::Load("assets/", true);
    ResourceManager::Load("../Undefined/resource_manager/", true );
    Interface::Init();

    BaseShader = ResourceManager::Get<Shader>("baseShader");


    if (BaseShader->ID)
    {
        BaseShader->Use();
    }

    InitVikingRoom();

    DirectionalLight = DirLight(Vector3(-1.f, -1.f, 1.f), {0.1f,0.1f,0.5f}, BASE_DIFFUSE, BASE_SPECULAR);
}

// move to wrapper
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


// move to wrapper
void Application::InitVikingRoom()
{
    std::shared_ptr<Model> model = ResourceManager::Get<Model>("assets/viking_room.obj");

    glGenBuffers(1, &mVBO);
    glGenVertexArrays(1, &mVAO);

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (model->VertexBuffer.size() * sizeof(Vertex)),
        model->VertexBuffer.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureUV));
    glEnableVertexAttribArray(2);

}

void Application::Update()
{
    T += 0.016f;

    ServiceLocator::Get<Renderer>()->SetClearColor();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ResourceManager::Get<Texture>("assets/viking_room.png")->GetID());

    ServiceLocator::Get<Window>()->GetCamera()->ProcessInput(ServiceLocator::Get<Window>()->GetWindowVar());
    ServiceLocator::Get<Window>()->GetCamera()->Update();

    // modify the camera in the shader
    BaseShader->Use();
    BaseShader->SetMat4("vp", ServiceLocator::Get<Window>()->GetCamera()->GetVP());
    BaseShader->SetVec3("viewPos", ServiceLocator::Get<Window>()->GetCamera()->Eye);


    BaseShader->SetMat4("model", Matrix4x4::TRS(Vector3(0), sin(T), Vector3(1.f, 0.f, 0.f), Vector3(1)));

    // TO MOVE TO LIGHTS UPDATE WHEN RESMANAGER WORKS WITH SHADER
    BaseShader->SetVec3("dirLights[0].direction", DirectionalLight.rot);
    BaseShader->SetVec3("dirLights[0].ambient", DirectionalLight.Ambient);
    BaseShader->SetVec3("dirLights[0].diffuse", DirectionalLight.Diffuse);
    BaseShader->SetVec3("dirLights[0].specular", DirectionalLight.Specular);


    BaseShader->Use();
    Draw();

    Interface::Update();
}

void Application::Draw()
{
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)ResourceManager::Get<Model>("assets/viking_room.obj")->VertexBuffer.size());
}
