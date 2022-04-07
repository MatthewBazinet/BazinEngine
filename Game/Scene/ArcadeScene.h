#ifndef ARCADESCENE_H
#define ARCADESCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include "../Character.h"
#include "../../Projectile.h"
#include "../../Flocking.h"
#include "../Pawn.h"
#include "../ParticleSystem.h"
#include "../InputManager.h"
#include <vector>

class ArcadeScene : public Scene
{
public:
	ArcadeScene();
	~ArcadeScene();
	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
	void NotifyOfKeyDown(const SDL_Scancode key_);
	void NotifyOfKeyUp(const SDL_Scancode key_);

	void ResetRound();
	void LoadPlayer1Character();
	void LoadPlayer2Character();
	void SetPlayerSettings();

	float scale;
	InputManager inputManager;

	glm::vec4 leftPlane;
	glm::vec4 rightPlane;
	glm::vec4 northPlane;
	glm::vec4 southPlane;
	std::vector<glm::vec4> planes;
};

#endif;