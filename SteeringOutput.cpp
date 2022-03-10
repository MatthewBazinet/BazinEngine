#include "SteeringOutput.h"

SteeringOutput::SteeringOutput()
{
	linear = glm::vec3(0);
	angular = 0.0f;
}

SteeringOutput::SteeringOutput(glm::vec3 linear_, float angular_)
{
	linear = linear_;
	angular = angular_;
}
