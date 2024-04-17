#include "application.h"

#include <glad/glad.h>
#include <iostream>
#include <filesystem>
#include <stb_image/stb_image.h>

#include "service_locator.h"

#include "resources/texture.h"
#include "resources/model.h"
#include "resources/model_renderer.h"
#include "resources/resource_manager.h"

#include "world/components/skybox.h"

#include "memory_leak.h"

#include "interface/interface.h"
#include "interface/inspector.h"

#include "interface/runtime_classes.h"

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

    RuntimeClasses::AddType<Component>();
    RuntimeClasses::AddType<Light>();
    RuntimeClasses::AddType<DirLight>();
    RuntimeClasses::AddType<ModelRenderer>();

    ResourceManager::Load("../Undefined/resource_manager/", true);
    ResourceManager::Load("assets/", true);

    // Callback
    ServiceLocator::SetupCallbacks();

    Interface::Init();
    Inspector::Init();

    Skybox::Setup();
    BaseShader = ResourceManager::Get<Shader>("base_shader");
    ResourceManager::Get<Model>("assets/viking_room.obj")->SetTexture(0, ResourceManager::Get<Texture>("assets/viking_room.png"));

    ActualScene.AddObject("DirLight")->AddComponent<DirLight>();
    ActualScene.AddObject("PikingRoom")->AddComponent<ModelRenderer>()->ModelObject = ResourceManager::Get<Model>("assets/viking_room.obj");
}

void Application::Update()
{
    mRenderer->SetClearColor(0,0,0);

    ActualScene.Update();
    Camera::ProcessInput();
    Interface::Update(&ActualScene);

    for (int i = 0; i < Interface::EditorViewports.size(); i++)
    {
        Interface::EditorViewports[i]->RescaleViewport();
        Interface::EditorViewports[i]->ViewportCamera->Update();
        Skybox::Update(Interface::EditorViewports[i]->ViewportCamera);

        mRenderer->BindFramebuffer(GL_FRAMEBUFFER, Interface::EditorViewports[i]->GetFBO_ID());

        mRenderer->EnableTest(GL_DEPTH_TEST);

        mRenderer->SetClearColor(0,0,0);
        mRenderer->ClearBuffer();
        
        mRenderer->UseShader(BaseShader->ID);

        mRenderer->SetUniform(BaseShader->ID ,"vp", Interface::EditorViewports[i]->ViewportCamera->GetVP());
        mRenderer->SetUniform(BaseShader->ID ,"viewPos", Interface::EditorViewports[i]->ViewportCamera->Eye);

        for (int j = 0; j < ActualScene.Objects.size(); j++)
        {
            mRenderer->SetUniform(BaseShader->ID, "EntityID", j);
        }

        ActualScene.Draw();

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
