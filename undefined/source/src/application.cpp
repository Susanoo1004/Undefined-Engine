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

    // Skybox::Setup();
    BaseShader = ResourceManager::Get<Shader>("base_shader");
    pickingShader = ResourceManager::Get<Shader>("picking_shader");
    ResourceManager::Get<Model>("assets/viking_room.obj")->SetTexture(0, ResourceManager::Get<Texture>("assets/viking_room.png"));

    Object* light = ActualScene.AddObject("Light");
    light->AddComponent<Light>();
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

    ServiceLocator::Get<Renderer>()->SetClearColor(0,0,0);

    // modify the camera in the shader
    pickingShader->Use();
    pickingShader->SetMat4("model", Matrix4x4::TRS(Vector3(0), sin(T), Vector3(1.f, 0.f, 0.f), Vector3(1)));

    //// modify the camera in the shader
    //BaseShader->Use();
    //BaseShader->SetMat4("model", Matrix4x4::TRS(Vector3(0), sin(T), Vector3(1.f, 0.f, 0.f), Vector3(1)));

    ActualScene.Update();

    //Skybox::Update();
    Interface::EditorViewports[0]->ViewportCamera->ProcessInput();

    for (int i = 0; i < Interface::EditorViewports.size(); i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, Interface::EditorViewports[i]->GetFBO_ID());
        glEnable(GL_DEPTH_TEST);

        glClearColor(0.f, 0.f, 0.f, 1);

        Interface::EditorViewports[i]->ViewportCamera->Update();

        mRenderer->ClearBuffer();
        /*BaseShader->UnUse();
        BaseShader->Use();

        BaseShader->SetMat4("vp", Interface::EditorViewports[i]->ViewportCamera->GetVP());
        BaseShader->SetVec3("viewPos", Interface::EditorViewports[i]->ViewportCamera->mEye);*/

        pickingShader->UnUse();
        pickingShader->Use();
        pickingShader->SetMat4("vp", Interface::EditorViewports[i]->ViewportCamera->GetVP());
        pickingShader->SetVec3("viewPos", Interface::EditorViewports[i]->ViewportCamera->mEye);

        for (int j = 0; j < Interface::EditorViewports[i]->mFramebuffer->RenderedTextures.size(); j++)
        {
           /* if (j == 0)
            {
                mRenderer->UseShader(BaseShader->ID);
            }

            else 
            {*/
                mRenderer->UseShader(pickingShader->ID);
            //}

            Draw(); 
            mRenderer->UnUseShader();
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

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

    // Last draw
    // Skybox::Draw();
}
