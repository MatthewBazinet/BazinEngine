#ifndef GJKTESTSCENE_H
#define GJKTESTSCENE_H

#include "../../Engine/Core/CoreEngine.h"

class GJKTestScene : public Scene
{
public:
	GJKTestScene();
	~GJKTestScene();
	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
	void NotifyOfKeyDown(const SDL_Scancode key_);
	void NotifyOfKeyUp(const SDL_Scancode key_);

	bool colliding = false;
};

#endif // !GJKTESTSCENE_H