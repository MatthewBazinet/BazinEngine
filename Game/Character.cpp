#include "Character.h"

void Character::QCF(int strength, bool simpleInput)
{
	if (isAirborne)
	{
		AirQCF(strength, simpleInput);
	}
}

void Character::QCB(int strength, bool simpleInput)
{
	if (isAirborne)
	{
		AirQCB(strength, simpleInput);
	}
}

void Character::Unique()
{

	
	if (isAirborne)
	{
		AirUnique();
	}
}

void Character::Light()
{
	if (isAirborne)
	{
		AirLight();
	}
}

void Character::Medium()
{
	if (isAirborne)
	{
		AirMedium();
	}
}

void Character::Heavy()
{
	if (isAirborne)
	{
		AirHeavy();
	}

}

void Character::Run(bool isRunning)
{
}

void Character::Move(glm::vec2 input)
{
}

void Character::AirQCF(int strength, bool simpleInput)
{
}

void Character::AirQCB(int strength, bool simpleInput)
{
}

void Character::AirUnique()
{
}

void Character::AirLight()
{
}

void Character::AirMedium()
{
}

void Character::AirHeavy()
{
}
