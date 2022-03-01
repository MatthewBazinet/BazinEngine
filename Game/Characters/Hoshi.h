#ifndef HOSHI_H
#define HOSHI_H

#include "..//Character.h"
#include "../HurtBox.h"
#include "../HitBox.h"
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

protected:
	void AirQCF(int strength, bool simpleInput);
	void AirQCB(int strength, bool simpleInput);
	void AirUnique();
	void AirLight();
	void AirMedium();
	void AirHeavy();

	Projectile* proj;
	bool floating;
};

#endif
