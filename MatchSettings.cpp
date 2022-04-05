#include "MatchSettings.h"
#include <iostream>

std::unique_ptr<MatchSettings> MatchSettings::MatchSettingsInstance = nullptr;
MatchSettings::MatchSettings()
{
	player1Character = Player1Characters::None;
	player2Character = Player2Characters::None;
	gameMode = GameMode::Arcade;
}
MatchSettings::~MatchSettings()
{
	OnDestroy();
}

MatchSettings* MatchSettings::GetInstance()
{
	if (MatchSettingsInstance.get() == nullptr)
	{
		MatchSettingsInstance.reset(new MatchSettings);
	}
	return MatchSettingsInstance.get();
}

bool MatchSettings::OnCreate()
{
	return true;
}

void MatchSettings::OnDestroy()
{
}

void MatchSettings::Update(const float deltaTime_)
{
}

void MatchSettings::StartTimer()
{
	timerStarted = true;
}

void MatchSettings::PauseTimer()
{
	timerStarted = false;
}

int MatchSettings::GetTimer()
{
	return time;
}

void MatchSettings::SetGameTime(int time_)
{
	time = time_;
}

void MatchSettings::SetPlayer1Character(Player1Characters character_)
{
	player1Character = character_;
}

void MatchSettings::SetPlayer2Character(Player2Characters character_)
{
	player2Character = character_;
}

Player1Characters MatchSettings::GetPlayer1Character()
{
	return player1Character;
}

Player2Characters MatchSettings::GetPlayer2Character()
{
	return player2Character;
}

void MatchSettings::NextMatch()
{
	player2Character = static_cast<Player2Characters>(static_cast<int>(player2Character) + 1);
}
