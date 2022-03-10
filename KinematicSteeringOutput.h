#ifndef KINEMATICSTEERINGOUTPUT_H
#define KINEMATICSTEERINGOUTPUT_H

#include<glm/glm.hpp>
class KinematicSteeringOutput
{
public:

	glm::vec3 velocity;
	float rotation;
	
	KinematicSteeringOutput();
	KinematicSteeringOutput(glm::vec3 velocity_, float rotation_);

};

#endif