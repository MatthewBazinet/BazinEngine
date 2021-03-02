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
