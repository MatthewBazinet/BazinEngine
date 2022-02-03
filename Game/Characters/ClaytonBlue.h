#ifndef CLAYTONBLUE_H
#define CLAYTONBLUE_H

#include "..//Character.h"

class ClaytonBlue : public Character
{
public:
	ClaytonBlue();
	~ClaytonBlue();

	void QCF(int strength, bool simpleInput);
	void QCB(int strength, bool simpleInput);
	void Unique();
	void Light();
	void Medium();
	void Heavy();
};

#endif
