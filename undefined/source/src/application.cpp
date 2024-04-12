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

#include <toolbox/calc.h>

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

    // Skybox::Setup();
    BaseShader = ResourceManager::Get<Shader>("base_shader");
    ResourceManager::Get<Model>("assets/viking_room.obj")->SetTexture(0, ResourceManager::Get<Texture>("assets/viking_room.png"));

    ActualScene.AddObject("DirLight")->AddComponent<DirLight>();
    Object* object = ActualScene.AddObject("PikingRoom");
    object->AddComponent<ModelRenderer>()->ModelObject = ResourceManager::Get<Model>("assets/viking_room.obj");
    
    object->GameTransform->Rotation = { -90, 0, 0 };
    //object->GameTransform->Scale = { 2, 1, 1 };
}

void Application::Update()
{
    T += 0.016f;

    mRenderer->SetClearColor(0,0,0);

    Camera::ProcessInput();
    Interface::Update();
    // To del
    Transform* trans = ActualScene.Objects[1]->GameTransform;
    //trans->Position = { std::sinf(T), -1, std::cosf(T) };
    ActualScene.Update();
    
    Logger::Debug("World Transform :\n{}\n{}\n{}\n", trans->Position, trans->Rotation, trans->Scale);
    
    Logger::Debug("Local Transform :\n{}\n{}\n{}", trans->LocalPosition, trans->LocalRotation, trans->LocalScale);
    Logger::Debug("Local");
    for (size_t i = 0; i < 4; i++)
    {
        Matrix4x4 mat = ActualScene.Objects[1]->GameTransform->WorldToLocalMatrix();
        auto test1 = mat[i][0];
        auto test2 = mat[i][1];
        auto test3 = mat[i][2];
        auto test4 = mat[i][3];
        Logger::Debug("{},{},{},{}", test1, test2, test3, test4);
    }
    Logger::Debug("World");
    for (size_t i = 0; i < 4; i++)
    {
        Matrix4x4 mat = ActualScene.Objects[1]->GameTransform->LocalToWorldMatrix();
        auto test1 = mat[i][0];
        auto test2 = mat[i][1];
        auto test3 = mat[i][2];
        auto test4 = mat[i][3];
        Logger::Debug("{},{},{},{}", test1, test2, test3, test4);
    }
    /*

    Logger::Debug("World");
    for (size_t i = 0; i < 4; i++)
    {
        Matrix4x4 mat = ActualScene.Objects[1]->GameTransform->LocalToWorldMatrix();
        auto test1 = mat[i][0];
        auto test2 = mat[i][1];
        auto test3 = mat[i][2];
        auto test4 = mat[i][3];
        Logger::Debug("{},{},{},{}", test1, test2, test3, test4);
    }
    Logger::Debug("");
    Logger::Debug("");
    */

    for (int i = 0; i < Interface::EditorViewports.size(); i++)
    {
        Interface::EditorViewports[i]->RescaleViewport();
        Interface::EditorViewports[i]->ViewportCamera->Update();
        // Skybox::Update(Interface::EditorViewports[i]->ViewportCamera);

        mRenderer->BindFramebuffer(GL_FRAMEBUFFER, Interface::EditorViewports[i]->GetFBO_ID());

        mRenderer->EnableTest(GL_DEPTH_TEST);

        mRenderer->SetClearColor(0,0,0);
        mRenderer->ClearBuffer();
        
        mRenderer->UseShader(BaseShader->ID);

        mRenderer->SetUniform(BaseShader->ID ,"vp", Interface::EditorViewports[i]->ViewportCamera->GetVP());
        mRenderer->SetUniform(BaseShader->ID ,"viewPos", Interface::EditorViewports[i]->ViewportCamera->Eye);

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
