#ifndef KEYBOARDEVENTLISTENER
#define KEYBOARDEVENTLISTENER

#include <SDL.h>
#include <glm/glm.hpp>
#include <string>
class CoreEngine;
class KeyboardEventListener {
public:
	KeyboardEventListener(const KeyboardEventListener&) = delete;
	KeyboardEventListener(KeyboardEventListener&&) = delete;
	KeyboardEventListener& operator=(const KeyboardEventListener) = delete;
	KeyboardEventListener& operator=(KeyboardEventListener&&) = delete;
	KeyboardEventListener() = delete;
	~KeyboardEventListener();

	static void RegisterEngineObject(CoreEngine* engine_);
	static void Update(SDL_Event e_);
	static void NotifyOfKeyPressed(SDL_Scancode key);
	static void NotifyOfKeyReleased(SDL_Scancode key);


private:
	static CoreEngine* engineInstance;

};


#endif // !KEYBOARDEVENTLISTENER
