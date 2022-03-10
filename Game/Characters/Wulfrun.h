#ifndef WULFRUN_H
#define WULFRUN_H

#include "..//Character.h"

class Wulfrun : public Character
{
public:
	Wulfrun(glm::vec3 pos);
	~Wulfrun();

	void Update(const float deltaTime_);

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
};

#endif
