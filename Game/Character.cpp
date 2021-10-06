#include "Character.h"

Character::Character(float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : GameObject(model_, position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_)
{
	health = health_;
	meter = meter_;
	isRunning = isRunning_;
	isAirborne = isAirborne_;
}

Character::~Character() {}

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
