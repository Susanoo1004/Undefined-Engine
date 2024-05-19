#include "application.h"

#include <iostream>
#include <filesystem>
#include <stdlib.h>
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <toolbox/calc.h>

#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>

#include "service_locator.h"

#include "wrapper/time.h"
#include "wrapper/physics_system.h"

#include "resources/texture.h"
#include "resources/model.h"
#include "resources/model_renderer.h"
#include "resources/resource_manager.h"

#include "world/dir_light.h"
#include "world/skybox.h"

#include "memory_leak.h"

#include "world/scene_manager.h"
#include "world/box_collider.h"
#include "world/capsule_collider.h"

#include "interface/interface.h"
#include "interface/inspector.h"

#include "reflection/runtime_classes.h"

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

    std::vector<int> a = { GLFW_KEY_SPACE };

    ServiceLocator::Get<InputManager>()->CreateKeyInput("debug", a);

    //Physics
    PhysicsSystem::Init();

    RuntimeClasses::AddType<Component>();
    RuntimeClasses::AddType<Light>();
    RuntimeClasses::AddType<DirLight>();
    RuntimeClasses::AddType<ModelRenderer>();

    ResourceManager::Load("../undefined/resource_manager/", true);
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

    SceneManager::ActualScene->AddObject("Floor");
    SceneManager::ActualScene->Objects[1]->GameTransform->Position = Vector3(0, -1, 0);
    SceneManager::ActualScene->Objects[1]->AddComponent<BoxCollider>(SceneManager::ActualScene->Objects[1]->GameTransform->GetPosition(), SceneManager::ActualScene->Objects[1]->GameTransform->GetRotationQuat(), Vector3(100.0f, 1.0f, 100.0f), true);

    Object* object = SceneManager::ActualScene->AddObject("PikingRoom");
    object->GameTransform->Position = Vector3(0, -0.5f, 0);
    object->AddComponent<ModelRenderer>()->ModelObject = ResourceManager::Get<Model>("assets/viking_room.obj");
    
    Object* sphere = SceneManager::ActualScene->AddObject("Sphere");
    sphere->GameTransform->Position = Vector3(0, 4, 0);
    sphere->AddComponent<ModelRenderer>()->ModelObject = ResourceManager::Get<Model>("assets/sphere.obj");
    CapsuleCollider* c = sphere->AddComponent<CapsuleCollider>(sphere->GameTransform->GetPosition(), sphere->GameTransform->GetRotationQuat(), 1, 1);

    PhysicsSystem::SetVelocity(c->BodyID ,Vector3(0, -1, 0));

    SceneManager::Start();
}

void Application::Update()
{
    Time::SetTimeVariables();

    mRenderer->SetClearColor(0,0,0);

    Camera::ProcessInput();
    SceneManager::GlobalUpdate();
    Interface::Update();
    
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

        SceneManager::Draw();

        mRenderer->UnUseShader();

        mRenderer->BindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    EditorViewport::SetIsGizmoUpdated(false);

    Interface::Render();

    mWindowManager->SwapBuffers();
    mRenderer->ClearBuffer();
    Logger::CheckForExit();
}

void Application::Clear()
{
    SceneManager::Delete();
    delete Camera::CurrentCamera;
    PhysicsSystem::Terminate();
    mRenderer->UnUseShader();
    ServiceLocator::CleanServiceLocator();
    ResourceManager::UnloadAll();
    Interface::Delete();
    Logger::Stop();
}
