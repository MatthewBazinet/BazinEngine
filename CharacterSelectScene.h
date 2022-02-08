#ifndef CHARACTERSELECTSCENE_H
#define CHARACTERSELECTSCENE_H
#include "../../Engine/Core/CoreEngine.h"
#include "../UserInterface.h"
#include "..//NetworkingBase.h"
#include "../SDLMusic.h"
#include <thread>
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

	static std::vector<Character*> GetHurtBoxes() {return hurtBoxes;};

	static std::vector<Character*> SetHurtBoxes(std::vector<Character*> hurtBoxes_) { hurtBoxes = hurtBoxes_; };

private:
	static std::vector<Character*> hurtBoxes;
};
#endif
