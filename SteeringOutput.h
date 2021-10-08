#pragma once
#include<glm/glm.hpp>
class SteeringOutput 
{
public:
	glm::vec3 linear;
	float angular;

	SteeringOutput();
	SteeringOutput(glm::vec3 linear_, float angular_);
	inline const SteeringOutput operator + (const SteeringOutput& v) const {
		return SteeringOutput(linear + v.linear, angular + v.angular);
	}
	inline const SteeringOutput operator + (const SteeringOutput& v) {
		linear += v.linear;
		angular += v.angular;
		return *this;
	}

};