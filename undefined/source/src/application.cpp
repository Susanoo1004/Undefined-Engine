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

#include "world/dir_light.h"
#include "world/skybox.h"

#include "memory_leak.h"

#include "world/scene_manager.h"

#include "interface/interface.h"
#include "interface/inspector.h"

#include <toolbox/calc.h>

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

    SceneManager::Init();

    SceneManager::ActualScene->AddObject("DirLight")->AddComponent<DirLight>();
    Object* object = SceneManager::ActualScene->AddObject("PikingRoom");
    object->AddComponent<ModelRenderer>()->ModelObject = ResourceManager::Get<Model>("assets/viking_room.obj");
    
    SceneManager::ActualScene->AddObject(object, "Test Child");
}

void Application::Update()
{
    mRenderer->SetClearColor(0,0,0);

    Camera::ProcessInput();
    Interface::Update(SceneManager::ActualScene);

    SceneManager::ActualScene->Objects[1]->GameTransform->Position += Vector3{ 0.1f, 0, 0 } * 0.016;
    SceneManager::ActualScene->Objects[1]->GameTransform->Rotation += Vector3{ 72.f, 0, 0 } * 0.016;


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

        for (int j = 0; j < SceneManager::ActualScene->Objects.size(); j++)
        {
            mRenderer->SetUniform(BaseShader->ID, "EntityID", SceneManager::ActualScene->Objects[j]);
        }

        SceneManager::ActualScene->Draw();

        mRenderer->UnUseShader();

        mRenderer->BindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Interface::Render();

    mWindowManager->SwapBuffers();
    mRenderer->ClearBuffer();
}

void Application::Clear()
{
    SceneManager::Delete();
    delete Camera::CurrentCamera;
    mRenderer->UnUseShader();
    ServiceLocator::CleanServiceLocator();
    ResourceManager::UnloadAll();
    Interface::Delete();
    Logger::Stop();
}
