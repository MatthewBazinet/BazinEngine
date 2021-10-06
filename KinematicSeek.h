#pragma once
#include "Projectile.h"
#include "KinematicSteeringOutput.h"
class KinematicSeek
{
private:
	KinematicSteeringOutput* result;
	Projectile* character;
	
	glm::vec3 target;

public:
	KinematicSeek(Projectile* character_, glm::vec3 target_);
	~KinematicSeek();
	KinematicSteeringOutput getSteering();
};


