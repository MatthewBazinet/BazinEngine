#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "..//Events/EventListener.h"
class GameInterface
{
public:
	GameInterface() {}
	virtual ~GameInterface() {}

	virtual bool OnCreate() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;
	void NotifyOfKeyDown(const SDL_Scancode key_);
	void NotifyOfKeyUp(const SDL_Scancode key_);
private:
};
#endif

