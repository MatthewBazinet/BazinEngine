#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h"

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
	GameObject* shape;
	Model* model;
};

#endif // !GAMESCENE_H