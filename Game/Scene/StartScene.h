#ifndef STARTSCENE_H
#define STARTSCENE_H
#include "../../Engine/Core/CoreEngine.h"
#include "../UserInterface.h"
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
	UserInterface* ui;

};

#endif // !STARTSCENE_H