#include "UserInterface.h"
#include "Engine/Core/CoreEngine.h"
#include <iostream>
#include <chrono>
#include <thread>

UserInterface::UserInterface()
{
	se.AddSoundEffects("Resources/Audio/mixkit-retro-game-notification-212.wav");
	menu = true;
	state = Menu;
}

UserInterface::~UserInterface()
{
}

void UserInterface::CreateUI(float health)
{
}

void UserInterface::DestroyUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	se.~SoundEffects();
}

bool UserInterface::OnCreate()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(CoreEngine::GetInstance()->GetWindow(), &io);
	ImGui_ImplOpenGL3_Init("#version 450");
	progress = 200.0f;
	damage = 0.01f;
	progress = glm::normalize(progress);


	return true;
}

void UserInterface::Update(const float deltaTime_)
{
	switch (CoreEngine::GetInstance()->GetCurrentScene())
	{
	case 1:
		ShowGameUi();
		break;
	case 2:
		
		break;
	default: //case 0:
		ShowMenu();
		break;
	}
}

void UserInterface::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::StartTimer()
{
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		time -= 1;
		if (time == 0) {
			break;
		}
	}
}
//Menu Ui
void UserInterface::ShowMenu()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	if (state == Menu) {


		//Single Player Button
		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.5f, CoreEngine::GetInstance()->GetScreenHeight() * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("here ", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		if (ImGui::Button("Single Player", ImVec2(300, 100))) {
			se.playSoundEffect(0);
			CoreEngine::GetInstance()->SetCurrentScene(1);
		}
		//Online Button
		if (ImGui::Button("Online", ImVec2(300, 100))) {
			se.playSoundEffect(0);
			state = Online;

		}



		ImGui::End();
		//Quit Button
		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.5f, CoreEngine::GetInstance()->GetScreenHeight() * 0.7f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("quit ", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		if (ImGui::Button("Quit", ImVec2(250, 90))) {
			CoreEngine::GetInstance()->Exit();
		}
		ImGui::End();
	}

	if(state == Online){
		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.5f, CoreEngine::GetInstance()->GetScreenHeight() * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Online Selection ", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		if (ImGui::Button("Host", ImVec2(250, 90))) {
			
		}
		if (ImGui::Button("Join", ImVec2(250, 90))) {
			std::thread net(&NetworkingBase::Run, false, str0);
			net.detach();
		}
		if (ImGui::InputText("Host IP", str0, IM_ARRAYSIZE(str0))) {
			
 		}
		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.15f, CoreEngine::GetInstance()->GetScreenHeight() * 0.1f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Menu Button", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		if (ImGui::Button("Back", ImVec2(250, 90))) {
			se.playSoundEffect(0);
			state = Menu;
		}
		ImGui::End();
	}

	
}

//Ui for in game
void UserInterface::ShowGameUi()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	//Player 1 Health Bar
	ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.75f, CoreEngine::GetInstance()->GetScreenHeight() * 0.05f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::Begin("Player 2", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs);
	ImGui::ProgressBar(progress,ImVec2(400,35));
	ImGui::End();

	//Player 2 Health Bar
	ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.25f, CoreEngine::GetInstance()->GetScreenHeight() * 0.05f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::Begin("Player 1", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs);
	ImGui::ProgressBar(progress, ImVec2(400, 35));
	ImGui::End();

	//Timer
	ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.5f, CoreEngine::GetInstance()->GetScreenHeight() * 0.05f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::Begin("Timer", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs);
	ImGui::Text("%i", time);
	ImGui::End();

	//gonna remove once we can damage characters
	progress -= damage;
	if (progress <= 0.0f) {
		progress = 1.0f;
	}
}

bool UserInterface::TextBox()
{
	return false;
}


