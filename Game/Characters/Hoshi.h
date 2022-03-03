#ifndef HOSHI_H
#define HOSHI_H

#include "..//Character.h"
#include "../Projectile.h"
#include "../Kunai.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class HurtBox;
class Hoshi : public Character
{
public:
	Hoshi(glm::vec3 pos_);
	~Hoshi();

	virtual void Update(const float deltaTime_);
	void SetModels(Model* model_, Model* hurtBox_);

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

	Projectile* proj;
	Model* kunai;
	bool floating;
};

#endif
