#include "UserInterface.h"

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}

void UserInterface::CreateUI()
{

}

void UserInterface::DestroyUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

bool UserInterface::OnCreate()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(CoreEngine::GetInstance()->GetWindow(), &io);
	ImGui_ImplOpenGL3_Init("#version 450");
	return true;
}

void UserInterface::Update(const float deltaTime_)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	
	ImGui::SetNextWindowPos(ImVec2(CoreEngine::GetInstance()->GetScreenWidth() / 2, CoreEngine::GetInstance()->GetScreenHeight() / 2));
	flags = ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground;
	ImGui::Begin("here ", NULL, flags);
	if (ImGui::Button("Play", ImVec2(300,100))) {
		CoreEngine::GetInstance()->SetCurrentScene(1);
	}
	ImGui::End();
}

void UserInterface::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
