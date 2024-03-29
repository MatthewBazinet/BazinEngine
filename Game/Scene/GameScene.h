#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include "../Character.h"
#include "../../Projectile.h"
#include "../../Flocking.h"
#include "../Pawn.h"
#include "../ParticleSystem.h"
#include <vector>
#include "../InputManager.h"
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
	void NotifyOfKeyDown(const SDL_Scancode key_);
	void NotifyOfKeyUp(const SDL_Scancode key_);

	void ResetRound();

	Component* ptr;
	float scale;
	bool tmp = true;
	InputManager inputManager;

	glm::vec4 leftPlane;
	glm::vec4 rightPlane;
	glm::vec4 northPlane;
	glm::vec4 southPlane;
	std::vector<glm::vec4> planes;
};

#endif // !GAMESCENE_H