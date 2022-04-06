#ifndef MATCHSETTINGS_H
#define MATCHSETTINGS_H

#include <chrono>
#include <thread>

#include "Game/Character.h"
enum class Player1Characters {
	None,
	Hoshi,
	Alexis,
	Eldric,
};
enum class Player2Characters {
	None,
	Hoshi,
	Alexis,
	Eldric
};
enum class GameMode {
	Versus,
	Arcade,
	Training
};
class MatchSettings
{
public:
	MatchSettings(const MatchSettings&) = delete;
	MatchSettings(MatchSettings&&) = delete;
	MatchSettings& operator=(const MatchSettings&) = delete;
	MatchSettings& operator=(MatchSettings&&) = delete;

	static MatchSettings* GetInstance();

	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime_);
	void StartTimer();
	void PauseTimer();
	int GetTimer();
	void SetGameTime(int time_);
	void SetPlayer1Character(Player1Characters character_);
	void SetPlayer2Character(Player2Characters character_);
	void SetGameMode(GameMode gamemode_);
	Player1Characters GetPlayer1Character();
	Player2Characters GetPlayer2Character();
	GameMode GetGameMode();
	void NextMatch();

	int GetP1Points() { return player1Points; };
	void SetP1Points(int points_) { player1Points = points_; };

	int GetP2Points() { return player2Points; };
	void SetP2Points(int points_) { player2Points = points_; };
private:
	MatchSettings();
	~MatchSettings();
	static std::unique_ptr<MatchSettings> MatchSettingsInstance;
	friend std::default_delete<MatchSettings>;
	bool timerStarted;
	int time = 400;

	Player1Characters player1Character;
	Player2Characters player2Character;
	GameMode gamemode;

	int player1Points;
	int player2Points;
};
#endif
