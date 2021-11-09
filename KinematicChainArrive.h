#ifndef KINEMATICCHAINARRIVE_H
#define KINEMATICCHAINARRIVE_H

#include "AICharacter.h"
#include "KinematicSteeringOutput.h"

class KinematicChainArrive
{
public:
	static int counter;

	static KinematicSteeringOutput getSteering(GameObject* character_, std::vector<glm::vec3> targets_, float timeToTarget_);
	static float LookAt(glm::vec3 velocity);
};

#endif;