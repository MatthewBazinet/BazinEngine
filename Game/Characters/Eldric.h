#ifndef ELDRIC_H
#define ELDRIC_H

#include "..//Character.h"
#include "../Projectile.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Eldric : public Character
{
public:
	Eldric(glm::vec3 pos_, Model* hurtBox_);
	~Eldric();

	virtual void Update(const float deltaTime_);

	void Run(bool isRunning_);
	void Move(glm::vec2 input);
	void OnLand();

	void QCF(int strength, bool simpleInput);
	void QCB(int strength, bool simpleInput);
	void Unique();
	void Light();
	void Medium();
	void Heavy();

	void ResetProjectile();

protected:
	void AirQCF(int strength, bool simpleInput);
	void AirQCB(int strength, bool simpleInput);
	void AirUnique();
	void AirLight();
	void AirMedium();
	void AirHeavy();

	void OnQCFActive(int strength);
	void OnQCBActive(int strength);
	void OnUniqueActive();
	void OnLightActive();
	void OnMediumActive();
	void OnHeavyActive();
	void OnAirQCFActive(int strength);
	void OnAirQCBActive(int strength);
	void OnAirUniqueActive();
	void OnAirLightActive();
	void OnAirMediumActive();
	void OnAirHeavyActive();

	void OnHeavyRecovery();
	void OnMediumRecovery();

	Projectile* proj;
};

#endif
