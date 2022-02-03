#ifndef ALEXISBRUCE_H
#define ALEXISBRUCE_H

#include "..//Character.h"

class AlexisBruce : public Character
{
public:
	AlexisBruce();
	~AlexisBruce();

	void QCF(int strength, bool simpleInput);
	void QCB(int strength, bool simpleInput);
	void Unique();
	void Light();
	void Medium();
	void Heavy();
};

#endif
