#ifndef STARTSCENE_H
#define STARTSCENE_H
#include "../../Engine/Core/CoreEngine.h"
class StartScene : public Scene
{
public:
	StartScene();
	~StartScene();
	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
	void NotifyOfKeyDown(const SDL_Scancode key_);
	void NotifyOfKeyUp(const SDL_Scancode key_);

private:
	GameInterface* gui;

};

#endif // !STARTSCENE_H