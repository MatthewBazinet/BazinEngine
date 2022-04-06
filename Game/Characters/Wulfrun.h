#ifndef WULFRUN_H
#define WULFRUN_H

#include "..//Character.h"

class Wulfrun : public Character
{
public:
	Wulfrun(glm::vec3 pos);
	~Wulfrun();

	void Update(const float deltaTime_);

	void Run(bool isRunning_);

	void Move(glm::vec2 input);

	void QCF(int strength, bool simpleInput);
	void QCB(int strength, bool simpleInput);
	void Unique();
	void Light();
	void Medium();
	void Heavy();

	void ResetProjectiles();
	void RemoveProjectile(std::string tag_);

protected:
	void AirQCF(int strength, bool simpleInput);
	void AirQCB(int strength, bool simpleInput);
	void AirUnique();
	void AirLight();
	void AirMedium();
	void AirHeavy();

	void OnQCFActive(int strength);
	void OnQCFRecovery(int strength);
	void OnQCBActive(int strength);
	void OnQCBRecovery(int strength);
	void OnUniqueActive();
	void OnHeavyActive();
	void OnAirQCFActive(int strength);
	void OnAirQCBActive(int strength);
	void OnAirUniqueActive();
	void OnAirHeavyActive();

	std::vector<Projectile*> projs;
};

#endif
