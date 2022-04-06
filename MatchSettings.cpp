#include "MatchSettings.h"
#include <iostream>

std::unique_ptr<MatchSettings> MatchSettings::MatchSettingsInstance = nullptr;
MatchSettings::MatchSettings()
{
	player1Character = Player1Characters::None;
	player2Character = Player2Characters::None;
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

void MatchSettings::SetGameMode(GameMode gamemode_)
{
	gamemode = gamemode_;
}

Player1Characters MatchSettings::GetPlayer1Character()
{
	return player1Character;
}

Player2Characters MatchSettings::GetPlayer2Character()
{
	return player2Character;
}

GameMode MatchSettings::GetGameMode()
{
	return gamemode;
}


