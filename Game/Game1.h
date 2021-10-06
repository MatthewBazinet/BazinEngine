#ifndef GAME1_H
#define GAME1_H

#include "..//Engine/Core/CoreEngine.h"
#include "Scene/StartScene.h"
#include "Scene/GameScene.h"

class Game1 : public GameInterface 
{
public:
	Game1();
	~Game1();
	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
	void HandleEvents(const SDL_Event& sdlEvent);
	void NotifyOfKeyDown(const SDL_Scancode key_);
	void NotifyOfKeyUp(const SDL_Scancode key_);
private:
	int currentSceneNum;
	Scene* currentScene;
	void BuildScene();

};

#endif // !GAME1_H
