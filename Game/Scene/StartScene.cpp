#include "StartScene.h"


StartScene::StartScene()
{
	network = new NetworkingBase();
	music.addMusicTrack("Resources/Audio/Dee Yan-Key - Postludio.mp3");
}

StartScene::~StartScene()
{
	
	delete network;
	network = nullptr;
	music.Play_Pause();
	
}

bool StartScene::OnCreate()
{
	Log::Info("Start Scene initiated", "StartScene.cpp", __LINE__);
	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	music.playMusicTrack(0);
	
	return true;
}

void StartScene::Update(const float deltaTime_)
{
	//CoreEngine::GetInstance()->SetCurrentScene(1);
}

void StartScene::Render()
{
}

void StartScene::HandleEvents(const SDL_Event& sdlEvent)
{
}

void StartScene::NotifyOfKeyDown(const SDL_Scancode key_)
{
	switch (key_)
	{	
		case SDL_SCANCODE_O:
			//network->CallRun(true);
			break;
		case SDL_SCANCODE_L:
			//std::thread net(&NetworkingBase::Run, false);
			//net.detach();
			break;
	}
}

void StartScene::NotifyOfKeyUp(const SDL_Scancode key_)
{
}
