#ifndef VIPIN_H
#define VIPIN_H

#include "..//Character.h"

class Vipin : public Character
{
public:
	Vipin();
	~Vipin();

	void QCF(int strength, bool simpleInput);
	void QCB(int strength, bool simpleInput);
	void Unique();
	void Light();
	void Medium();
	void Heavy();
};

#endif
