#include "Game1.h"

Game1::Game1() : GameInterface(), currentScene(nullptr), currentSceneNum(0)
{
	window = nullptr;
}

Game1::~Game1() 
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	delete window;
	window = nullptr;
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate() 
{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForOpenGL(CoreEngine::GetInstance()->GetWindow() , &io);
		ImGui_ImplOpenGL3_Init("#version 450");



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
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();


	ImGui::Begin("hello");
	ImGui::Text("well then");
	ImGui::End();
	currentScene->Update(deltaTime_);

}

void Game1::Render()
{


	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
