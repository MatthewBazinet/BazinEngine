#include "StartScene.h"

StartScene::StartScene()
{
	ui = new UserInterface();
	network = new NetworkingBase();
}

StartScene::~StartScene()
{
	ui->DestroyUI();
	delete ui;
	ui = nullptr;
	
}

bool StartScene::OnCreate()
{
	Log::Info("Start Scene initiated", "StartScene.cpp", __LINE__);
	ui->OnCreate();
	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	
	return true;
}

void StartScene::Update(const float deltaTime_)
{
	//CoreEngine::GetInstance()->SetCurrentScene(1);
	ui->Update(deltaTime_);
}

void StartScene::Render()
{
	ui->Render();
}

void StartScene::HandleEvents(const SDL_Event& sdlEvent)
{
}

void StartScene::NotifyOfKeyDown(const SDL_Scancode key_)
{
	switch (key_)
	{
		case SDL_SCANCODE_O:
			network->Run(true);
			break;
		case SDL_SCANCODE_L:
			network->Run(false);
			break;
	}
}

void StartScene::NotifyOfKeyUp(const SDL_Scancode key_)
{
}
