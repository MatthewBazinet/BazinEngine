#include "InputManager.h"

InputManager::InputManager()
{
	time = 0.0f;
}

InputManager::~InputManager()
{
	player1 = nullptr;
	player2 = nullptr;
}

void InputManager::SetPlayer1(Character* player1_)
{
	player1 = player1_;
}

void InputManager::SetPlayer2(Character* player2_)
{
	player2 = player2_;
}

void InputManager::SetPlayer1Keybinds(Keybinds player1Keybinds_)
{
	player1Keybinds = player1Keybinds_;
}

void InputManager::SetPlayer2Keybinds(Keybinds player2Keybinds_)
{
	player2Keybinds = player2Keybinds_;
}

void InputManager::OnKeyDown(SDL_Scancode key_)
{
	if (player1) {
		if (key_ == player1Keybinds.up)
		{
			player1Inputs.directions.back().y = 1.0f;
			player1->Move(player1Inputs.directions.back());
		}
		else if (key_ == player1Keybinds.down)
		{
			player1Inputs.directions.back().y = -1.0f;
			player1Inputs.timeDownHeld = time;
			player1->Move(player1Inputs.directions.back());
		}
		else if (key_ == player1Keybinds.left)
		{
			player1Inputs.directions.back().x = -1.0f;
			player1Inputs.timeLeftHeld = time;
			player1->Move(player1Inputs.directions.back());
		}
		else if (key_ == player1Keybinds.right)
		{
			player1Inputs.directions.back().x = 1.0f;
			player1Inputs.timeRightHeld = time;
			player1->Move(player1Inputs.directions.back());
		}
		else if (key_ == player1Keybinds.light)
		{
			player1Inputs.lightPressed = true;
			CheckMotion(0, 1);
		}
		else if (key_ == player1Keybinds.medium)
		{
			player1Inputs.mediumPressed = true;
			CheckMotion(1, 1);
		}
		else if (key_ == player1Keybinds.heavy)
		{
			player1Inputs.heavyPressed = true;
			CheckMotion(2, 1);
		}
		else if (key_ == player1Keybinds.unique)
		{
			player1Inputs.uniquePressed = true;
			player1->Unique();
		}
		else if (key_ == player1Keybinds.run)
		{
			player1Inputs.runPressed = true;
			player1->Run(true);
		}
		else if (key_ == player1Keybinds.super)
		{
			player1Inputs.superPressed = true;
		}
		else if (key_ == player1Keybinds.shortcutForward)
		{
			player1Inputs.shortcutForwardPressed = true;
		}
		else if (key_ == player1Keybinds.shortcutBackward)
		{
			player1Inputs.shortcutBackwardPressed = true;
		}
	}
	if (player2)
	{
		if (key_ == player2Keybinds.up)
		{
			player2Inputs.directions.back().y = 1.0f;
			player2->Move(player2Inputs.directions.back());
		}
		else if (key_ == player2Keybinds.down)
		{
			player2Inputs.directions.back().y = -1.0f;
			player2Inputs.timeDownHeld = time;
			player1->Move(player1Inputs.directions.back());
		}
		else if (key_ == player2Keybinds.left)
		{
			player2Inputs.directions.back().x = -1.0f;
			player2Inputs.timeLeftHeld = time;
			player1->Move(player1Inputs.directions.back());
		}
		else if (key_ == player2Keybinds.right)
		{
			player2Inputs.directions.back().x = 1.0f;
			player2Inputs.timeRightHeld = time;
			player1->Move(player1Inputs.directions.back());
		}
		else if (key_ == player2Keybinds.light)
		{
			player2Inputs.lightPressed = true;
			CheckMotion(0, 2);
		}
		else if (key_ == player2Keybinds.medium)
		{
			player2Inputs.mediumPressed = true;
			CheckMotion(1, 2);
		}
		else if (key_ == player2Keybinds.heavy)
		{
			player2Inputs.heavyPressed = true;
			CheckMotion(2, 2);
		}
		else if (key_ == player2Keybinds.unique)
		{
			player2Inputs.uniquePressed = true;
			player2->Unique();
		}
		else if (key_ == player2Keybinds.run)
		{
			player2Inputs.runPressed = true;
			player2->Run(true);
		}
		else if (key_ == player2Keybinds.super)
		{
			player2Inputs.superPressed = true;
		}
		else if (key_ == player2Keybinds.shortcutForward)
		{
			player2Inputs.shortcutForwardPressed = true;
		}
		else if (key_ == player2Keybinds.shortcutBackward)
		{
			player2Inputs.shortcutBackwardPressed = true;
		}
	}
}

void InputManager::OnKeyUp(SDL_Scancode key_)
{
	if (player1)
	{
		if (key_ == player1Keybinds.up)
		{
			if (player1Inputs.directions.back().y == 1.0f)
			{
				player1Inputs.directions.back().y = 0.0f;
			}
			player1->Move(player1Inputs.directions.back());
		}
		else if (key_ == player1Keybinds.down)
		{
			if (player1Inputs.directions.back().y == -1.0f)
			{
				player1Inputs.directions.back().y = 0.0f;
			}
			player1Inputs.timeDownGrace = chargeGracePeriod;
			player1->Move(player1Inputs.directions.back());
		}
		else if (key_ == player1Keybinds.left)
		{
			if (player1Inputs.directions.back().x == -1.0f)
			{
				player1Inputs.directions.back().x = 0.0f;
			}
			player1Inputs.timeLeftGrace = chargeGracePeriod;
			player1->Move(player1Inputs.directions.back());
		}
		else if (key_ == player1Keybinds.right)
		{
			if (player1Inputs.directions.back().x == 1.0f)
			{
				player1Inputs.directions.back().x = 0.0f;
			}
			player1Inputs.timeRightGrace = chargeGracePeriod;
			player1->Move(player1Inputs.directions.back());
		}
		else if (key_ == player1Keybinds.light)
		{
			player1Inputs.lightPressed = false;
		}
		else if (key_ == player1Keybinds.medium)
		{
			player1Inputs.mediumPressed = false;
		}
		else if (key_ == player1Keybinds.heavy)
		{
			player1Inputs.heavyPressed = false;
		}
		else if (key_ == player1Keybinds.unique)
		{
			player1Inputs.uniquePressed = false;
		}
		else if (key_ == player1Keybinds.run)
		{
			player1Inputs.runPressed = false;
			player1->Run(false);
		}
		else if (key_ == player1Keybinds.super)
		{
			player1Inputs.superPressed = false;
		}
		else if (key_ == player1Keybinds.shortcutForward)
		{
			player1Inputs.shortcutForwardPressed = false;
		}
		else if (key_ == player1Keybinds.shortcutBackward)
		{
			player1Inputs.shortcutBackwardPressed = false;
		}
	}
	if (player2)
	{
		if (key_ == player2Keybinds.up)
		{
			if (player2Inputs.directions.back().y == 1.0f)
			{
				player2Inputs.directions.back().y = 0.0f;
			}
			player2->Move(player2Inputs.directions.back());
		}
		else if (key_ == player2Keybinds.down)
		{
			if (player2Inputs.directions.back().y == -1.0f)
			{
				player2Inputs.directions.back().y = 0.0f;
			}
			player2Inputs.timeDownGrace = chargeGracePeriod;
			player2->Move(player2Inputs.directions.back());
		}
		else if (key_ == player2Keybinds.left)
		{
			if (player2Inputs.directions.back().x == -1.0f)
			{
				player2Inputs.directions.back().x = 0.0f;
			}
			player2Inputs.timeLeftGrace = chargeGracePeriod;
			player2->Move(player2Inputs.directions.back());
		}
		else if (key_ == player2Keybinds.right)
		{
			if (player2Inputs.directions.back().x == 1.0f)
			{
				player2Inputs.directions.back().x = 0.0f;
			}
			player2Inputs.timeRightGrace = chargeGracePeriod;
			player2->Move(player2Inputs.directions.back());
		}
		else if (key_ == player2Keybinds.light)
		{
			player2Inputs.lightPressed = false;
		}
		else if (key_ == player2Keybinds.medium)
		{
			player2Inputs.mediumPressed = false;
		}
		else if (key_ == player2Keybinds.heavy)
		{
			player2Inputs.heavyPressed = false;
		}
		else if (key_ == player2Keybinds.unique)
		{
			player2Inputs.uniquePressed = false;
		}
		else if (key_ == player2Keybinds.run)
		{
			player2Inputs.runPressed = false;
			player2->Run(false);
		}
		else if (key_ == player2Keybinds.super)
		{
			player2Inputs.superPressed = false;
		}
		else if (key_ == player2Keybinds.shortcutForward)
		{
			player2Inputs.shortcutForwardPressed = false;
		}
		else if (key_ == player2Keybinds.shortcutBackward)
		{
			player2Inputs.shortcutBackwardPressed = false;
		}
	}
}

void InputManager::Update(const float deltaTime_)
{
	time += deltaTime_;
	if(player1)	player1Inputs.Update(deltaTime_);
	if(player2) player2Inputs.Update(deltaTime_);

}

void InputManager::CheckMotion(int strength, int character)
{
	Character* characterObject = nullptr;
	CharacterInput* input = nullptr;

	if (character == 1)
	{
		characterObject = player1;
		input = &player1Inputs;
	}
	else
	{
		characterObject = player2;
		input = &player2Inputs;
	}

	if (input->shortcutForwardPressed)
	{
		if (characterObject->IsCharge())
		{
			if(characterObject->FacingLeft())
			{ 
				if (time - input->timeRightHeld > 1.0f || input->timeRightHeld > 0.0f)
				{
					characterObject->QCF(strength, true);
					input->timeRightHeld = 0.0f;
				}
				else
				{
					switch (strength)
					{
					case 0:
						characterObject->Light();
						break;
					case 1:
						characterObject->Medium();
						break;
					case 2:
						characterObject->Heavy();
						break;
					default:
						break;
					}
				}
			}
			else 
			{
				if (time - input->timeLeftHeld > 1.0f || input->timeLeftHeld > 0.0f)
				{
					characterObject->QCF(strength, true);
					input->timeLeftHeld = 0.0f;
				}
				else
				{
					switch (strength)
					{
					case 0:
						characterObject->Light();
						break;
					case 1:
						characterObject->Medium();
						break;
					case 2:
						characterObject->Heavy();
						break;
					default:
						break;
					}
				}
			}
		}
		else 
		{
			characterObject->QCF(strength, true);
		}
	}
	else if (input->shortcutBackwardPressed)
	{
		if (characterObject->IsCharge())
		{
			if (time - input->timeDownHeld > 1.0f || input->timeDownHeld > 0.0f)
			{
				characterObject->QCB(strength, true);
				input->timeDownHeld = 0.0f;
			}
			else
			{
				switch (strength)
				{
				case 0:
					characterObject->Light();
					break;
				case 1:
					characterObject->Medium();
					break;
				case 2:
					characterObject->Heavy();
					break;
				default:
					break;
				}
			}
		}
		else
		{
			characterObject->QCB(strength, true);
		}
	}
	/*else if (!characterObject->IsCharge() && input->directions.back().y == 0.0f)
		{
		bool isChecking = true;
		bool downForward = false;
		bool downBack = false;
		bool usedSpecial = false;
		bool facingLeft = characterObject->FacingLeft();
		if (input->directions.back().x == -1.0f) {

		}
		int i = 1;
				do {
					
					glm::vec2 dirs = input->directions[input->directions.size() - i];
					if (dirs.y == -1.0f)
					{
						if ((dirs.x == 1.0f && !facingLeft) || (dirs.x == -1.0f && facingLeft))
						{
							if (downBack)
							{
								isChecking = false;
							}
							else
							{
								downForward == true;
							}
						}
						if ((dirs.x == -1.0f && !facingLeft) || (dirs.x == 1.0f && facingLeft))
						{
							if (downForward)
							{
								isChecking = false;
							}
							else
							{
								downBack == true;
							}
						}
					}
					else if(dirs.y == 0.0f && (dirs.x == 1.0f && !facingLeft) || (dirs.x == -1.0f && facingLeft))
					{
						if (downForward)
						{
							characterObject->QCF(strength, false);
							usedSpecial = true;
							isChecking = false;
						}
					}
					else if (dirs.y == 0.0f && (dirs.x == -1.0f && !facingLeft) || (dirs.x == 1.0f && facingLeft))
					{
						if (downBack)
						{
							characterObject->QCB(strength, false);
							usedSpecial = true;
							isChecking = false;
						}
					}
					else
					{
						isChecking = false;
					}
					i++;
					if (i >= input->directions.size())
					{
						isChecking = false;
					}
				} while (isChecking);
				if (!usedSpecial)
				{
					switch (strength)
					{
					case 0:
						characterObject->Light();
						break;
					case 1:
						characterObject->Medium();
						break;
					case 2:
						characterObject->Heavy();
						break;
					default:
						break;
					}
				}
	}*/
	else
	{
		switch (strength)
		{
		case 0:
			characterObject->Light();
			break;
		case 1:
			characterObject->Medium();
			break;
		case 2:
			characterObject->Heavy();
			break;
		default:
			break;
		}
	}


	characterObject = nullptr;
	input = nullptr;
}

CharacterInput::CharacterInput()
{
	directions.push_back(glm::vec2());
	lightPressed = false;
	mediumPressed = false;
	heavyPressed = false;
	uniquePressed = false;
	runPressed = false;
	superPressed = false;
	shortcutForwardPressed = false;
	shortcutBackwardPressed = false;
}

void CharacterInput::Update(const float deltaTime_)
{
	directions.push_back(glm::vec2(directions.back().x, directions.back().y));
	if (directions.size() > 120)
	{
		directions.pop_front();
	}
	if (timeDownGrace > 0.0f)
	{
		timeDownGrace -= deltaTime_;
		if (timeDownGrace <= 0.0f)
		{
			timeDownHeld = 0.0f;
			timeDownGrace = 0.0f;
		}
	}
	if (timeLeftGrace > 0.0f)
	{
		timeLeftGrace -= deltaTime_;
		if (timeLeftGrace <= 0.0f)
		{
			timeLeftHeld = 0.0f;
			timeLeftGrace = 0.0f;
		}
	}
	if (timeRightGrace > 0.0f)
	{
		timeRightGrace -= deltaTime_;
		if (timeRightGrace <= 0.0f)
		{
			timeRightHeld = 0.0f;
			timeRightGrace = 0.0f;
		}
	}
}
