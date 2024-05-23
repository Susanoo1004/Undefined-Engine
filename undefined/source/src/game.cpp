#include "game.h"

Game::Game()
{
}

void Game::Init()
{
	PhysicsSystem::Init();

    SceneManager::Init();

    SceneManager::ActualScene->AddObject("Point")->AddComponent<PointLight>(Vector3{ 0.4f, 0.4f, 0.4f }, Vector3{ 0.8f, 0.8f, 0.8f }, Vector3{ 0.5f, 0.5f, 0.5f }, 1.0f, 0.09f, 0.032f);

    Object* floor = SceneManager::ActualScene->AddObject("Floor");
    floor->GameTransform->Position = Vector3(0, -2, 0);
    floor->GameTransform->SetRotation(Vector3(0, 0.f, 5));
    floor->AddComponent<BoxCollider>(floor->GameTransform->GetPosition(), floor->GameTransform->GetRotationQuat(), Vector3(100.0f, 2.0f, 100.0f), true);


    Object* object = SceneManager::ActualScene->AddObject("PikingRoom");
    object->GameTransform->Position = Vector3(0, -0.5f, 0);
    object->AddComponent<ModelRenderer>()->ModelObject = ResourceManager::Get<Model>("assets/viking_room.obj");

    Object* object2 = SceneManager::ActualScene->AddObject("PikingRoom2");
    object2->GameTransform->Position = Vector3(2, -0.5f, 0);
    std::shared_ptr<Model> mode = object2->AddComponent<ModelRenderer>()->ModelObject = ResourceManager::Get<Model>("assets/viking_room.obj");
    mode->SetTexture(0, ResourceManager::Get<Texture>("assets/pacman.png"));


    Object* sphere = SceneManager::ActualScene->AddObject("Sphere");
    sphere->GameTransform->Position = Vector3(0, 1.f, 0);
    sphere->AddComponent<ModelRenderer>()->ModelObject = ResourceManager::Get<Model>("assets/sphere.obj");
    CapsuleCollider* c = sphere->AddComponent<CapsuleCollider>(sphere->GameTransform->GetPosition(), sphere->GameTransform->GetRotationQuat(), 1, 1);

    //SOUND
    mSoundDevice = SoundDevice::Get();

    sound1 = SoundBuffer::Get()->AddSoundEffect(ResourceManager::Get<Audio>("audio/fazbear.wav"));
    sound2 = SoundBuffer::Get()->AddSoundEffect(ResourceManager::Get<Audio>("audio/desert.wav"));

    mSoundSource = new SoundSource;
    source1 = mSoundSource->CreateSource();
    source2 = mSoundSource->CreateSource();

    mKeyInput = ServiceLocator::Get<InputManager>()->GetKeyInput("editorCameraInput");
}

void Game::Update()
{
    SceneManager::GlobalUpdate();
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

    mSoundDevice->SetPosition(Interface::EditorViewports[0]->ViewportCamera->CurrentCamera->Eye);
    mSoundDevice->SetOrientation(Interface::EditorViewports[0]->ViewportCamera->CurrentCamera->LookAt);
}

void Game::Terminate()
{
    SceneManager::Delete();
    PhysicsSystem::Terminate();
}
