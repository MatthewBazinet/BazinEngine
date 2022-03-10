#include "KinematicSteeringOutput.h"

KinematicSteeringOutput::KinematicSteeringOutput()
{
	velocity = glm::vec3(0, 0, 0);
	rotation = 0.0f;
}

KinematicSteeringOutput::KinematicSteeringOutput(glm::vec3 velocity_, float rotation_)
{
	velocity = velocity_;
	rotation = rotation_;
}
