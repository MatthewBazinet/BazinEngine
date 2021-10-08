#ifndef MATCHVELOCITY_H
#define MATCHVELOCITY_H
#include "Projectile.h"
#include "SteeringOutput.h"
class MatchVelocity
{
public:
	static SteeringOutput getSteering(GameObject* character_, GameObject* target_, float timeToTarget_, float maxAccel_);
private:
	//Projectile main;
	//Projectile target;

	//float maxAccel = 5.0f;
	//float timeToTarget = 0.1;
};
#endif
