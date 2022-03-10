#ifndef KINEMATICARRIVE_H
#define KINEMATICARRIVE_H

#include "Projectile.h"
#include "KinematicSteeringOutput.h"
class KinematicArrive
{
public:
	static KinematicSteeringOutput getSteering(GameObject* character_, glm::vec3 target_, float timeToTarget_);
	static float LookAt(glm::vec3 velocity);
};


#endif