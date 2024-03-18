#include "application.h"

#include <glad/glad.h>
#include <iostream>
#include <filesystem>

#include "service_locator.h"

#include "resources/texture.h"
#include "resources/model.h"
#include "resources/resource_manager.h"

#include "memory_leak.h"

#include "interface/interface.h"

Application::Application()
{
    ServiceLocator::Setup();

    mWindowManager = ServiceLocator::Get<Window>();
    mRenderer = ServiceLocator::Get<Renderer>();
}

void Application::Init()
{
    mWindowManager->Init();

    mRenderer->Init();

    // Callback
    ServiceLocator::SetupCallbacks();

    ResourceManager::Load("assets/", true);
    ResourceManager::Load("../Undefined/resource_manager/", true);
    Interface::Init();

    BaseShader = ResourceManager::Get<Shader>("baseShader");

    DirectionalLight = DirLight(Vector3(-1.f, -1.f, 1.f), BASE_AMBIENT, BASE_DIFFUSE, BASE_SPECULAR);

    ResourceManager::Get<Model>("assets/viking_room.obj")->SetTexture(0, ResourceManager::Get<Texture>("assets/viking_room.png"));

    Player* playerTest = new Player;
    Light* lightTest = new Light;
    Object* objectTest = new Object;
    objectTest->Components.push_back(playerTest);
    objectTest->Components.push_back(lightTest);

    ActualScene.Objects.push_back(objectTest);
}

// move to wrapper
void Application::InitQuad()
{
    float Vertices[] = {
        // positions          // normal           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int Indices[] = 
    {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), &Vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
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
}


void Application::Update()
{
    T += 0.016f;

    ActualScene.Update();

    ServiceLocator::Get<Renderer>()->SetClearColor();

    ServiceLocator::Get<Window>()->GetCamera()->ProcessInput();
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
    
    mWindowManager->SwapBuffers();
    mRenderer->ClearBuffer();
}

void Application::Clear()
{
    ServiceLocator::CleanServiceLocator();
    ResourceManager::UnloadAll();
    Interface::Delete();

    Logger::Stop();
}

void Application::Draw()
{
    ResourceManager::Get<Model>("assets/viking_room.obj")->Draw();
}
