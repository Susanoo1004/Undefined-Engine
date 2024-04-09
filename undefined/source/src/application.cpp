#include "application.h"

#include <glad/glad.h>
#include <iostream>
#include <filesystem>
#include <stb_image/stb_image.h>

#include "service_locator.h"

#include "resources/texture.h"
#include "resources/model.h"
#include "resources/resource_manager.h"

#include "world/components/skybox.h"

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
    ResourceManager::Load("assets/", true);
    ResourceManager::Load("../Undefined/resource_manager/", true);

    // Callback
    ServiceLocator::SetupCallbacks();

    Interface::Init();

    Skybox::Setup();
    BaseShader = ResourceManager::Get<Shader>("base_shader");
    ResourceManager::Get<Model>("assets/viking_room.obj")->SetTexture(0, ResourceManager::Get<Texture>("assets/viking_room.png"));

    ActualScene.AddObject("Light")->AddComponent<Light>();

    Object* object = ActualScene.AddObject("test1");
    Object* object2 = ActualScene.AddObject("test2");
    object2->SetParent(object);

    object->GameTransform->Rotation = { 90.f, 0.f, 0.f };
    for (size_t i = 0; i < 4; i++)
    {
        Matrix4x4 mat = object->GameTransform->WorldToLocalMatrix();
        auto test1 = mat[i][0];
        auto test2 = mat[i][1];
        auto test3 = mat[i][2];
        auto test4 = mat[i][3];
        Logger::Debug("{},{},{},{}", test1, test2, test3, test4);
    }
    Logger::Debug("");
    for (size_t i = 0; i < 4; i++)
    {
        Matrix4x4 mat = object2->GameTransform->WorldToLocalMatrix();
        auto test1 = mat[i][0];
        auto test2 = mat[i][1];
        auto test3 = mat[i][2];
        auto test4 = mat[i][3];
        Logger::Debug("{},{},{},{}", test1, test2, test3, test4);
    }

    Logger::Debug("");
    Logger::Debug("world");
    Logger::Debug("{}, {}, {}", object->GameTransform->Rotation.x, object->GameTransform->Rotation.y, object->GameTransform->Rotation.z);
    Logger::Debug("{}, {}, {}", object2->GameTransform->Rotation.x, object2->GameTransform->Rotation.y, object2->GameTransform->Rotation.z);

    Logger::Debug("local");
    Logger::Debug("{}, {}, {}", object->GameTransform->LocalRotation.x, object->GameTransform->LocalRotation.y, object->GameTransform->LocalRotation.z);
    Logger::Debug("{}, {}, {}", object2->GameTransform->LocalRotation.x, object2->GameTransform->LocalRotation.y, object2->GameTransform->LocalRotation.z);
    Logger::Debug("");

    Logger::Debug("");
    Logger::Debug("world scale");
    Logger::Debug("{}, {}, {}", object->GameTransform->Scale.x, object->GameTransform->Scale.y, object->GameTransform->Scale.z);
    Logger::Debug("{}, {}, {}", object2->GameTransform->Scale.x, object2->GameTransform->Scale.y, object2->GameTransform->Scale.z);

    Logger::Debug("local scale");
    Logger::Debug("{}, {}, {}", object->GameTransform->LocalScale.x, object->GameTransform->LocalScale.y, object->GameTransform->LocalScale.z);
    Logger::Debug("{}, {}, {}", object2->GameTransform->LocalScale.x, object2->GameTransform->LocalScale.y, object2->GameTransform->LocalScale.z);
    Logger::Debug("");

    object2->GameTransform->Rotation = { 0.f, 90.f, 0.f };

    for (size_t i = 0; i < 4; i++)
    {
        Matrix4x4 mat = object->GameTransform->WorldToLocalMatrix();
        auto test1 = mat[i][0];
        auto test2 = mat[i][1];
        auto test3 = mat[i][2];
        auto test4 = mat[i][3];
        Logger::Debug("{},{},{},{}", test1, test2, test3, test4);
    }
    Logger::Debug("");
    for (size_t i = 0; i < 4; i++)
    {
        Matrix4x4 mat = object2->GameTransform->WorldToLocalMatrix();
        auto test1 = mat[i][0];
        auto test2 = mat[i][1];
        auto test3 = mat[i][2];
        auto test4 = mat[i][3];
        Logger::Debug("{},{},{},{}", test1, test2, test3, test4);
    }
    Logger::Debug("");

    Logger::Debug("world");
    Logger::Debug("{}, {}, {}", object->GameTransform->Rotation.x, object->GameTransform->Rotation.y, object->GameTransform->Rotation.z);
    Logger::Debug("{}, {}, {}", object2->GameTransform->Rotation.x, object2->GameTransform->Rotation.y, object2->GameTransform->Rotation.z);

    Logger::Debug("local");
    Logger::Debug("{}, {}, {}", object->GameTransform->LocalRotation.x, object->GameTransform->LocalRotation.y, object->GameTransform->LocalRotation.z);
    Logger::Debug("{}, {}, {}", object2->GameTransform->LocalRotation.x, object2->GameTransform->LocalRotation.y, object2->GameTransform->LocalRotation.z);
    Logger::Debug("");
}

// move to RENDERER
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

    ServiceLocator::Get<Renderer>()->SetClearColor();

    mWindowManager->GetCamera()->ProcessInput();
    mWindowManager->GetCamera()->Update();

    // modify the camera in the shader
    BaseShader->Use();

    BaseShader->SetMat4("vp", mWindowManager->GetCamera()->GetVP());
    BaseShader->SetVec3("viewPos", mWindowManager->GetCamera()->mEye);

    BaseShader->SetMat4("model", Matrix4x4::TRS(Vector3(0), sin(T), Vector3(1.f, 0.f, 0.f), Vector3(1)));

    glBindFramebuffer(GL_FRAMEBUFFER, Interface::EditorViewports[0].GetFBO_ID());
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.3f, 0.3f, 0.3f, 1);

    BaseShader->UnUse();
    mRenderer->ClearBuffer();
    BaseShader->Use();

    ActualScene.Update();

    mRenderer->UseShader(BaseShader->ID);
    Draw();
    mRenderer->UnUseShader();

    Skybox::Update();
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Interface::Update();

    mWindowManager->SwapBuffers();
    mRenderer->ClearBuffer();
}

void Application::Clear()
{
    ServiceLocator::CleanServiceLocator();
    ResourceManager::UnloadAll();
    Interface::Delete();
    skyboxShader->UnUse();
    Logger::Stop();
}

void Application::Draw()
{
    ResourceManager::Get<Model>("assets/viking_room.obj")->Draw();

    ActualScene.Draw();
}
