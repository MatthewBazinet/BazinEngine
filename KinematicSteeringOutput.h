#pragma once
//fix
#include<glm/glm.hpp>
class KinematicSteeringOutput
{
public:

	glm::vec3 velocity;
	float rotation;

	KinematicSteeringOutput();
	KinematicSteeringOutput(glm::vec3 velocity_, float rotation_);

};

