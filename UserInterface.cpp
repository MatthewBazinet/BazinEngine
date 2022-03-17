#include "UserInterface.h"
#include "Engine/Core/CoreEngine.h"
#include <iostream>


std::unique_ptr<UserInterface> UserInterface::UserInterfaceInstance = nullptr;

UserInterface::UserInterface():state(State::Menu)
{

	se.AddSoundEffects("Resources/Audio/mixkit-retro-game-notification-212.wav");
}

UserInterface::~UserInterface()
{
}

UserInterface* UserInterface::GetInstance()
{
	if (UserInterfaceInstance.get() == nullptr)
	{
		UserInterfaceInstance.reset(new UserInterface);
	}
	return UserInterfaceInstance.get();
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
		timerStarted = false;
	return true;
}

void UserInterface::Update(const float deltaTime_)
{
	switch (CoreEngine::GetInstance()->GetCurrentScene())
	{
	case 0:
		ShowMenu();
		break;
	case 1:
		state = State::SinglePlayer;
		ShowGameUi();
		break;
	case 2:
		state = State::Empty;
		break;
	case 3:
		break;
	case 4:
		state = State::SinglePlayer;
		ShowGameUi();
		break;
	case 7:
		state = State::CharacterSelect;
		ShowCharacterSelect();
		break;
	default:
		state = State::Empty;
		break;
	}
}

void UserInterface::Render()
{
	if (state != State::Empty) {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	//ImGui_ImplOpenGL3_DestroyDeviceObjects();
}

void UserInterface::StartTimer()
{
	while (true){
		if (time > 0) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
			time -= 1;
		}
	}
}
//Menu Ui
void UserInterface::ShowMenu()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	if (state == State::Menu) {
		//Single Player Button
		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.5f, CoreEngine::GetInstance()->GetScreenHeight() * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("here ", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		if (ImGui::Button("Versus Mode", ImVec2(300, 100))) {
			se.playSoundEffect(0);
			CoreEngine::GetInstance()->SetCurrentScene(7);
		}

		if (ImGui::Button("Training Mode (WIP)", ImVec2(300, 100))) {
			se.playSoundEffect(0);
		}

		//Online Button
		if (ImGui::Button("Online", ImVec2(300, 100))) {
			se.playSoundEffect(0);
			state = State::Online;
		}
		ImGui::End();

		//Quit Button
		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.5f, CoreEngine::GetInstance()->GetScreenHeight() * 0.8f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("quit ", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		if (ImGui::Button("Quit", ImVec2(250, 90))) {
			CoreEngine::GetInstance()->Exit();
		}
		ImGui::End();
	}

	if(state == State::Online){
		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.5f, CoreEngine::GetInstance()->GetScreenHeight() * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Online Selection ", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		if (ImGui::Button("Host", ImVec2(250, 90))) {
			//std::thread net(&NetworkingBase::Run, true, str0);
			//net.detach();
		}
		if (ImGui::Button("Join", ImVec2(250, 90))) {
			//std::thread net(&NetworkingBase::Run, false, str0);
			//net.detach();
		}
		if (ImGui::InputText("Host IP", str0, IM_ARRAYSIZE(str0),ImGuiInputTextFlags_EnterReturnsTrue)) {
			std::cout << str0 << std::endl;
 		}
		ImGui::End();
		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.15f, CoreEngine::GetInstance()->GetScreenHeight() * 0.1f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Menu Button", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		if (ImGui::Button("Back", ImVec2(250, 90))) {
			se.playSoundEffect(0);
			state = State::Menu;
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
	if (!timerStarted) {
		std::cout << "Timer Started" << std::endl;
		time = MatchSettings::GetInstance()->GetTimer();
		std::thread Thread = std::thread(&UserInterface::StartTimer, this);
		Thread.detach();
		timerStarted = true;
	}
	if (state == State::SinglePlayer) {

		//Player 1 Health Bar & Overclock Meter
		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.75f, CoreEngine::GetInstance()->GetScreenHeight() * 0.05f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Player 2HP", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs);

		if (SceneGraph::GetInstance()->GetGameObject("char2")) {
			float health = (static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->GetHealth() - 0.0f) / (1000.0f - 0.0f);
			ImGui::ProgressBar(health, ImVec2(400, 35));
		}
		else {
			ImGui::ProgressBar(0.1, ImVec2(400, 35));
		}
		
		ImGui::End();
		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.675f, CoreEngine::GetInstance()->GetScreenHeight() * 0.1f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Player 2OC", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs);
		if (SceneGraph::GetInstance()->GetGameObject("char2")) {
			float overclock = (static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->GetOverclock() - 0.0f) / (100.0f - 0.0f);
			ImGui::ProgressBar(overclock, ImVec2(250, 25));
		}
		else {
			ImGui::ProgressBar(0.1, ImVec2(250, 25));
		}
		ImGui::End();

		//Player 2 Health Bar & Overclock Meter
		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.25f, CoreEngine::GetInstance()->GetScreenHeight() * 0.05f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Player 1HP", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs);
		if (SceneGraph::GetInstance()->GetGameObject("char1")) {
			float health = (static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->GetHealth() - 0.0f) / (1000.0f - 0.0f);
			ImGui::ProgressBar(health, ImVec2(400, 35));
		}
		else {
			ImGui::ProgressBar(0.1, ImVec2(400, 35));
		}
		ImGui::End();
		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.325f, CoreEngine::GetInstance()->GetScreenHeight() * 0.1f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Player 1OC", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs);
		if (SceneGraph::GetInstance()->GetGameObject("char1")) {
			float overclock = (static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->GetOverclock() - 0.0f) / (100.0f - 0.0f);
			ImGui::ProgressBar(overclock, ImVec2(250, 25));
		}
		else {
			ImGui::ProgressBar(0.1, ImVec2(250, 25));
		}
		ImGui::End();
		//Timer
		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.5f, CoreEngine::GetInstance()->GetScreenHeight() * 0.05f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Timer", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs);
		ImGui::Text("%i", time);
		ImGui::End();
	}
	else {
		state = State::Empty;
	}
}

void UserInterface::ShowCharacterSelect()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	if (state == State::CharacterSelect) {
		//Single Player Button
		ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() * 0.5f, CoreEngine::GetInstance()->GetScreenHeight() * 0.9f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("here ", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		ImGui::TextColored(ImVec4(1.0, 1.0, 1.0, 1.0), "A<								>D");
		if (ImGui::Button("Start Game", ImVec2(250, 80))) {
			se.playSoundEffect(0);
			CoreEngine::GetInstance()->SetCurrentScene(1);
		}
		
	}
		ImGui::End();
}

bool UserInterface::TextBox()
{
	return false;
}




