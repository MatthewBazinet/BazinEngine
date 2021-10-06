
#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Engine/Rendering/3D/GameObject.h"
<<<<<<< HEAD
#include "../Projectile.h"
	class Character : GameObject
=======

	class Character : public GameObject
>>>>>>> 6a6268eabfc0efe993d67520a2708d0aea0c2ac8
{
public:
	using GameObject::GameObject;

	Character(float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat orientation_ = glm::quat(0.0f, 5.0f, 5.0f, 5.0f), glm::quat angularVelocity_ = glm::quat());
	~Character();

	void QCF(int strength, bool simpleInput);
	void QCB(int strength, bool simpleInput);
	void Unique();
	void Light();
	void Medium();
	void Heavy();
	void Run(bool isRunning);
	void Move(glm::vec2 input);

<<<<<<< HEAD
=======
	bool getIsRunning() const { return isRunning; };
	bool getIsAirborne() const { return isAirborne; };

>>>>>>> 6a6268eabfc0efe993d67520a2708d0aea0c2ac8
private:
	void AirQCF(int strength, bool simpleInput);
	void AirQCB(int strength, bool simpleInput);
	void AirUnique();
	void AirLight();
	void AirMedium();
	void AirHeavy();

	float health;
	float meter;
	
	bool isRunning;
	bool isAirborne;
};

#endif