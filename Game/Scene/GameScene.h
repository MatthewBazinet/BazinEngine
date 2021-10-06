#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include "../Character.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
private:
	Character* char1;
};

#endif // !GAMESCENE_H