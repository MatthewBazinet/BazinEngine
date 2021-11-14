#include "UserInterface.h"
#include "Engine/Core/CoreEngine.h"
#include <iostream>
#include <chrono>
#include <thread>

UserInterface::UserInterface()
{
	se.AddSoundEffects("Resources/Audio/mixkit-retro-game-notification-212.wav");
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

void UserInterface::ShowMenu()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	

	ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.5f, CoreEngine::GetInstance()->GetScreenHeight() * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::Begin("here ", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
	if (ImGui::Button("Single Player", ImVec2(300, 100))) {
		se.playSoundEffect(0);
		CoreEngine::GetInstance()->SetCurrentScene(1);
	}

	if (ImGui::Button("Online", ImVec2(300, 100))) {
		se.playSoundEffect(0);
		std::thread net(&NetworkingBase::Run, false);
		net.detach();
	}
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.5f, CoreEngine::GetInstance()->GetScreenHeight() * 0.7f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::Begin("quit ", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
	if (ImGui::Button("Quit", ImVec2(250, 90))) {
		CoreEngine::GetInstance()->Exit();
	}
	ImGui::End();
}

void UserInterface::ShowGameUi()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin(" ", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs);
	ImGui::ProgressBar(progress,ImVec2(400,40));
	ImGui::Text("%i", time);
	
	progress -= damage;
	if (progress <= 0.0f) {
		progress = 1.0f;
	}
	ImGui::End();
}


