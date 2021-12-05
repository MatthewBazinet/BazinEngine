#ifndef SCENE2_H
#define SCENE2_H

#include "../../Engine/Core/CoreEngine.h"
#include "../Character.h"
#include "../../Projectile.h"
#include "../../Flocking.h"
#include "..//Pathfinding.h"
#include "../Decision Tree/FloatDecision.h"
#include "../Decision Tree/Action.h"
#include "../Game/TestChar.h"

class Scene2 : public Scene
{
public:
	Scene2();
	~Scene2();
	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
	void NotifyOfKeyDown(const SDL_Scancode key_);
	void NotifyOfKeyUp(const SDL_Scancode key_);
	
	GridWithWeights navgrid;
};

#endif // !GAMESCENE_H