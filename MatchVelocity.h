#ifndef MATCHVELOCITY_H
#define MATCHVELOCITY_H
#include "Projectile.h"
#include "SteeringOutput.h"
class MatchVelocity
{
public:
	static SteeringOutput getSteering(GameObject* character_, GameObject* target_, float timeToTarget_, glm::vec3 maxAccel_);

	MatchVelocity();
private:
	
	SteeringOutput result;

};
#endif
