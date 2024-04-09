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

    ResourceManager::Load("../Undefined/resource_manager/", true);
    ResourceManager::Load("assets/", true);

    // Callback
    ServiceLocator::SetupCallbacks();

    Interface::Init();

    Skybox::Setup();
    BaseShader = ResourceManager::Get<Shader>("base_shader");
    ResourceManager::Get<Model>("assets/viking_room.obj")->SetTexture(0, ResourceManager::Get<Texture>("assets/viking_room.png"));

   Object* light = ActualScene.AddObject("dirLight");
   light->AddComponent<DirLight>();
}

void Application::Update()
{
    T += 0.016f;

    mRenderer->SetClearColor(0,0,0);

    // Modify the camera in the shader
    BaseShader->Use();
    BaseShader->SetMat4("model", Matrix4x4::TRS(Vector3(0), sin(T), Vector3(1.f, 0.f, 0.f), Vector3(1)));

    ActualScene.Update();
    BaseShader->UnUse();

    Camera::ProcessInput();
    Interface::Update();

    for (int i = 0; i < Interface::EditorViewports.size(); i++)
    {
        Interface::EditorViewports[i]->RescaleViewport();

        mRenderer->BindFramebuffer(GL_FRAMEBUFFER, Interface::EditorViewports[i]->GetFBO_ID());

        mRenderer->EnableTest(GL_DEPTH_TEST);

        mRenderer->SetClearColor(0,0,0);

        Interface::EditorViewports[i]->ViewportCamera->Update();
        Skybox::Update(Interface::EditorViewports[i]->ViewportCamera);

        mRenderer->ClearBuffer();
        
        BaseShader->Use();

        BaseShader->SetMat4("vp", Interface::EditorViewports[i]->ViewportCamera->GetVP());
        BaseShader->SetVec3("viewPos", Interface::EditorViewports[i]->ViewportCamera->Eye);

        mRenderer->UseShader(BaseShader->ID);
        Draw();
        mRenderer->UnUseShader();

        mRenderer->BindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Interface::Render();

    mWindowManager->SwapBuffers();
    mRenderer->ClearBuffer();
}

void Application::Clear()
{
    delete Camera::CurrentCamera;
    mRenderer->UnUseShader();
    ServiceLocator::CleanServiceLocator();
    ResourceManager::UnloadAll();
    Interface::Delete();
    Logger::Stop();
}

void Application::Draw()
{
    ResourceManager::Get<Model>("assets/viking_room.obj")->Draw();

    // Last draw
    Skybox::Draw();
}
