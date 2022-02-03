#ifndef HOSHI_H
#define HOSHI_H

#include "..//Character.h"

class Hoshi : public Character
{
public:
	Hoshi();
	~Hoshi();

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
