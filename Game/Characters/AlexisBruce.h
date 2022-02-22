#ifndef ALEXISBRUCE_H
#define ALEXISBRUCE_H

#include "..//Character.h"
#include "../Projectile.h"

class HurtBox;
class AlexisBruce : public Character
{
public:
	AlexisBruce(float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), float angle_ = 0.0f, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat orientation_ = glm::quat(0.0f, 5.0f, 5.0f, 5.0f), glm::quat angularVelocity_ = glm::quat());
	~AlexisBruce();

	void NotifyOnKeyDown(SDL_Scancode key_);
	void NotifyOnKeyUp(SDL_Scancode key_);

	virtual void Update(const float deltaTime_);

	void SetModels(Model* rockModel_, Model* hurtBox_);
	void QCF(int strength, bool simpleInput);
	void QCB(int strength, bool simpleInput);
	void Unique();
	void Light();
	void Medium();
	void Heavy();
	void Run(bool isRunning_);
	void Move(glm::vec2 input);


protected:
	void AirQCF(int strength, bool simpleInput);
	void AirQCB(int strength, bool simpleInput);
	void AirUnique();
	void AirLight();
	void AirMedium();
	void AirHeavy();

	Model* rockModel;
	Model* hurtBoxM;
	Projectile* proj;
};

#endif
