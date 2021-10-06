#pragma once
#include "Projectile.h"
#include "KinematicSteeringOutput.h"
class KinematicSeek
{
public:
	static KinematicSteeringOutput getSteering(GameObject* character_, glm::vec3 target_);
	static float LookAt(glm::vec3 velocity);
};


