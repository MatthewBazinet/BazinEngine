#ifndef TRAININGSCENE_H
#define TRAININGSCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include "../Character.h"
#include "../../Projectile.h"
#include "../../Flocking.h"
#include "..//Pathfinding.h"
#include "../Decision Tree/FloatDecision.h"
#include "../Decision Tree/Action.h"
#include "../Game/TestChar.h"

class TrainingScene : public Scene
{
public:
	TrainingScene();
	~TrainingScene();
	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
	void NotifyOfKeyDown(const SDL_Scancode key_);
	void NotifyOfKeyUp(const SDL_Scancode key_);

	GridWithWeights navgrid;
	glm::vec4 leftPlane;
	glm::vec4 rightPlane;
	glm::vec4 northPlane;
	glm::vec4 southPlane;
	std::vector<glm::vec4> planes;
};

#endif;