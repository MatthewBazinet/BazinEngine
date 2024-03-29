#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <chrono>
#include <thread>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "SoundEffects.h"
#include "NetworkingBase.h"
#include "Game/Character.h"
#include "Engine/Core/Timer.h"

enum class State { Menu, Settings, Online, SinglePlayer, CharacterSelect, Empty };
class UserInterface
{
public:
	UserInterface(const UserInterface&) = delete;
	UserInterface(UserInterface&&) = delete;
	UserInterface& operator=(const UserInterface&) = delete;
	UserInterface& operator=(UserInterface&&) = delete;

	static UserInterface* GetInstance();

	void CreateUI(float health = 100.0f);
	void DestroyUI();

	bool OnCreate();
	void Update(const float deltaTime_);
	void Render();
	void StartTimer();
	void ShowMenu();
	void ShowGameUi();
	void ShowCharacterSelect();
	bool TextBox();

	void SetPlayer1(Character* character_);
	void SetPlayer2(Character* character_);

private:
	UserInterface();
	~UserInterface();
	State state;
	ImGuiBackendFlags flags;
	int time = 60;
	bool timerStarted;
	Character* player1;
	Character* player2;
	SoundEffects se;
	char str0[256] = { 0 };

	static std::unique_ptr<UserInterface> UserInterfaceInstance;
	friend std::default_delete<UserInterface>;
};

#endif // !USERINTERFACE_H