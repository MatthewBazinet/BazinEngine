#include "Game1.h"

#include "Scene/StartScene.h"
#include "Scene/GameScene.h"
#include "Scene/Scene2.h"
#include "../OnlineGameScene.h"
#include "..//GJKTestScene.h"

Game1::Game1() : GameInterface(), currentScene(nullptr), currentSceneNum(0)
{
}

Game1::~Game1() 
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate() 
{
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0)
	{
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}
	Log::Error("Engine's scene is not initialized to 0", "Game1.cpp", __LINE__);
	return false;
}

void Game1::Update(const float deltaTime_) 
{
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene()) 
	{
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game1::Render()
{
	currentScene->Render();
}

void Game1::HandleEvents(const SDL_Event& sdlEvent)
{
	currentScene->HandleEvents(sdlEvent);
}

void Game1::NotifyOfKeyDown(const SDL_Scancode key_)
{
	currentScene->NotifyOfKeyDown(key_);
}

void Game1::NotifyOfKeyUp(const SDL_Scancode key_)
{
	currentScene->NotifyOfKeyUp(key_);
}

void Game1::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::GetInstance()->GetCurrentScene()) 
	{
	case 1:
		currentScene = new GameScene();
		break;
	case 2:
		currentScene = new Scene2();
		break;
	case 3:
		currentScene = new GJKTestScene();
		break;
	case 4:
		currentScene = new OnlineGameScene();
		break;
	default: //case 0:
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate())
	{
		Log::Error("Scene failed to be created", "Game1.cpp", __LINE__);
		CoreEngine::GetInstance()->Exit();
	}
}
