#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include <glm/glm.hpp>
#include "Character.h"
#include <queue>
#include <utility>

struct CharacterInput
{
	std::deque<glm::vec2> directions;
	bool lightPressed;
	bool mediumPressed;
	bool heavyPressed;
	bool uniquePressed;
	bool runPressed;
	bool superPressed;
	bool shortcutForwardPressed;
	bool shortcutBackwardPressed;
	float timeRightHeld = 0.0f;
	float timeLeftHeld = 0.0f;
	float timeDownHeld = 0.0f;
	float timeRightGrace = 0.0f;
	float timeLeftGrace = 0.0f;
	float timeDownGrace = 0.0f;

	void Update(const float deltaTime_);
};

struct Keybinds
{
public:
	SDL_Scancode up;
	SDL_Scancode down;
	SDL_Scancode left;
	SDL_Scancode right;
	SDL_Scancode light;
	SDL_Scancode medium;
	SDL_Scancode heavy;
	SDL_Scancode unique;
	SDL_Scancode run;
	SDL_Scancode super;
	SDL_Scancode shortcutForward;
	SDL_Scancode shortcutBackward;

};

class InputManager
{
	InputManager();
	~InputManager();
	void SetPlayer1(Character* player1_);
	void SetPlayer2(Character* player2_);
	void SetPlayer1Keybinds(Keybinds player1Keybinds_);
	void SetPlayer2Keybinds(Keybinds player2Keybinds_);
	void OnKeyDown(SDL_Scancode key_);
	void OnKeyUp(SDL_Scancode key_);
	void Update(const float deltaTime_);

private:
	void CheckMotion(int strength, int character);

	Character* player1;
	Keybinds player1Keybinds;
	CharacterInput player1Inputs;

	Character* player2;
	Keybinds player2Keybinds;
	CharacterInput player2Inputs;

	float time;
	float chargeGracePeriod;
};

#endif // !INPUTMANAGER_H
