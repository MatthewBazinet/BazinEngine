#include "Hoshi.h"

Hoshi::Hoshi(float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : Character(health_, meter_, isRunning_, isAirborne_, model_, position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_)
{
	health = health_;
	overclock = meter_;
	isRunning = isRunning_;
	isAirborne = isAirborne_;
	model = model_;
	maxSpeed = 5.0f;

	target = glm::vec3();

}

Hoshi::~Hoshi()
{
	Character::~Character();
}

void Hoshi::NotifyOnKeyDown(SDL_Scancode key_)
{

}

void Hoshi::NotifyOnKeyUp(SDL_Scancode key_)
{

}

void Hoshi::Update(const float deltaTime_)
{
	if (hurtBox)
	{
		hurtBox->Update(deltaTime_);
	}
	Character::Update(deltaTime_);
}

void Hoshi::SetModels(Model* model_, Model* hurtBox_)
{
	hitBox = new HitBox(hurtBox_, this->position, this);
	hitBox->spawnSpheres(this->position, this->position + glm::vec3(0.0f, 12.0f, 0.0f), 2.0f, 4);

	//hurtBox = new HurtBox(hurtBox_, this->position, this);
	//hurtBox->SpawnHurtBox(hurtBox_, this->position, this->position + glm::vec3(5.0f, 12.0f, 0.0f), 2.0f, 4);
}