#ifndef KINEMATICFLEE_H
#define KINEMATICFLEE_H

#include "Projectile.h"
#include "KinematicSteeringOutput.h"

class KinematicFlee
{
public:
	static KinematicSteeringOutput getSteering(GameObject* character_, glm::vec3 target_);
	static float LookAt(glm::vec3 velocity);
};

#endif;