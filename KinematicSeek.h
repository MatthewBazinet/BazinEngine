#ifndef KINEMATICSEEK_H
#define KINEMATICSEEK_H

#include "Projectile.h"
#include "KinematicSteeringOutput.h"
class KinematicSeek
{
public:
	static KinematicSteeringOutput getSteering(GameObject* character_, glm::vec3 target_);
	static KinematicSteeringOutput PersueTarget(GameObject* character_, GameObject* target_);
	static float LookAt(glm::vec3 velocity);

private:
	

};


#endif