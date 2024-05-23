#include "application.h"

#include <iostream>
#include <filesystem>
#include <stdlib.h>
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <toolbox/calc.h>

#include "service_locator.h"

#include "wrapper/time.h"

#include "resources/texture.h"
#include "resources/model.h"
#include "resources/model_renderer.h"
#include "resources/resource_manager.h"

#include "world/dir_light.h"
#include "world/point_light.h"
#include "world/spot_light.h"
#include "world/skybox.h"

#include "memory_leak.h"

#include "world/scene_manager.h"

#include "interface/interface.h"
#include "interface/inspector.h"

#include "reflection/runtime_classes.h"

#include "resources/audio.h"
#include "audio/sound_buffer.h"

#include "world/player_test.h"

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

    RuntimeClasses::AddAllClasses();

    ResourceManager::Load("../undefined/resource_manager/", true);
    ResourceManager::Load("assets/", true);
    // Callback
    ServiceLocator::SetupCallbacks();

    Interface::Init();
    Inspector::Init();
    mKeyInput = ServiceLocator::Get<InputManager>()->GetKeyInput("editorCameraInput");

    Skybox::Setup();
    BaseShader = ResourceManager::Get<Shader>("base_shader");
    ResourceManager::Get<Model>("assets/viking_room.obj")->SetTexture(0, ResourceManager::Get<Texture>("assets/viking_room.png"));

    SceneManager::Init();

    SceneManager::ActualScene->AddObject("poin")->AddComponent<PointLight>(Vector3{ 0.4f, 0.4f, 0.4f }, Vector3{ 0.8f, 0.8f, 0.8f }, Vector3{ 0.5f, 0.5f, 0.5f }
    ,1.0f, 0.09f, 0.032f);

    Object* object = SceneManager::ActualScene->AddObject("PikingRoom");
    object->AddComponent<ModelRenderer>()->ModelObject = ResourceManager::Get<Model>("assets/viking_room.obj");

    SceneManager::ActualScene->AddObject(object, "Test Child");

    //SOUND
    mSoundDevice = SoundDevice::Get();

    sound1 = SoundBuffer::Get()->AddSoundEffect(ResourceManager::Get<Audio>("audio/fazbear.wav"));
    sound2 = SoundBuffer::Get()->AddSoundEffect(ResourceManager::Get<Audio>("audio/desert.wav"));

    mSoundSource = new SoundSource;
    source1 = mSoundSource->CreateSource();
    source2 = mSoundSource->CreateSource();
}

void Application::Update()
{
    Time::SetTimeVariables();

    mRenderer->SetClearColor(0,0,0);

    Camera::ProcessInput();
    SceneManager::GlobalUpdate();
    Interface::Update();
    Logger::Sync();

    mSoundSource->SetPosition(source1, Vector3());
    
    if (mKeyInput->GetIsKeyDown(GLFW_KEY_X))
    {
        mSoundSource->Play(source1, sound1);
    }

    if (mKeyInput->GetIsKeyDown(GLFW_KEY_C))
    {
        mSoundSource->Play(source2, sound2);
    }

    if (mKeyInput->GetIsKeyDown(GLFW_KEY_N))
    {
        mSoundSource->Resume(source1, sound1);
    }

    if (mKeyInput->GetIsKeyDown(GLFW_KEY_V))
    {
        mSoundSource->Stop(source1, sound1);
    }

    if (mKeyInput->GetIsKeyDown(GLFW_KEY_B))
    {
        mSoundSource->Restart(source1, sound1);
    }

    mSoundDevice->SetPosition(Camera::CurrentCamera == nullptr ? Camera::LastPos : Interface::EditorViewports[0]->ViewportCamera->CurrentCamera->Eye);
    mSoundDevice->SetOrientation(Camera::CurrentCamera == nullptr ? Camera::LastOrientation : Interface::EditorViewports[0]->ViewportCamera->CurrentCamera->LookAt);
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
    mRenderer->UnUseShader();
    ServiceLocator::CleanServiceLocator();
    ResourceManager::UnloadAll();
    Interface::Delete();
    Logger::Stop();
}
