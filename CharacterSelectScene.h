#ifndef CHARACTERSELECTSCENE_H
#define CHARACTERSELECTSCENE_H
#include "../Engine/Core/CoreEngine.h"
#include "../UserInterface.h"
#include "..//NetworkingBase.h"
#include "../SDLMusic.h"
#include <thread>
#include "MatchSettings.h"
#include "../ParticleSystem.h"
class CharacterSelectScene : public Scene
{
public:
	CharacterSelectScene();
	~CharacterSelectScene();
	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
	void NotifyOfKeyDown(const SDL_Scancode key_);
	void NotifyOfKeyUp(const SDL_Scancode key_);
	void AddCharacter(std::string P1Name_, GameObject* P1Character_, Player1Characters P1Enums_,std::string P2Name_, GameObject* P2Character_, Player2Characters P2Enums_);
	void CharacterSelection();
	//static std::vector<Character*> GetHurtBoxes() {return hurtBoxes;};
	//static std::vector<Character*> SetHurtBoxes(std::vector<Character*> hurtBoxes_) { hurtBoxes = hurtBoxes_; };
private:
	//static std::vector<Character*> hurtBoxes;
	std::vector<std::string> P1names;
	std::vector<std::string> P2names;

	std::unordered_map<std::string, GameObject*> P1ListOfCharacters;
	std::unordered_map<std::string, GameObject*> P2ListOfCharacters;

	std::unordered_map<std::string, Player1Characters> P1Enums;
	std::unordered_map<std::string, Player2Characters> P2Enums;

	std::string P1selectedCharacter;
	std::string P1currentCharacter;

	std::string P2selectedCharacter;
	std::string P2currentCharacter;

	int P1count;
	int P2count;
};
#endif