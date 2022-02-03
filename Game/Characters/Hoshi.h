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
};

#endif
