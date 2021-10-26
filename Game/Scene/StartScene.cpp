#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	Log::Info("Start Scene initiated", "StartScene.cpp", __LINE__);
	//CoreEngine::GetInstance()->SetCamera(new Camera());
	//CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));



	return true;
}

void StartScene::Update(const float deltaTime_)
{
	CoreEngine::GetInstance()->SetCurrentScene(1);
}

void StartScene::Render()
{
}

void StartScene::HandleEvents(const SDL_Event& sdlEvent)
{
}

void StartScene::NotifyOfKeyDown(const SDL_Scancode key_)
{
}

void StartScene::NotifyOfKeyUp(const SDL_Scancode key_)
{
}
