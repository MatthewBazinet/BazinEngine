#include "KeyboardEventListener.h"
#include "..//Core/CoreEngine.h"

CoreEngine* KeyboardEventListener::engineInstance = nullptr;


KeyboardEventListener::~KeyboardEventListener()
{
	engineInstance = nullptr;
}

void KeyboardEventListener::RegisterEngineObject(CoreEngine* engine_)
{
	engineInstance = engine_;
}

void KeyboardEventListener::Update(SDL_Event e_)
{
	switch (e_.type)
	{
	case SDL_KEYDOWN:
		NotifyOfKeyPressed(e_.key.keysym.scancode);
		break;
	case SDL_KEYUP:
		NotifyOfKeyReleased(e_.key.keysym.scancode);
	default:
		break;
	}


}

void KeyboardEventListener::NotifyOfKeyPressed(SDL_Scancode key)
{
	engineInstance->NotifyOfKeyDown(key);
}

void KeyboardEventListener::NotifyOfKeyReleased(SDL_Scancode key)
{
	engineInstance->NotifyOfKeyRelease(key);
}

