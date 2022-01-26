#ifndef SPHERE_H
#define SPHERE_H

#include<glm/glm.hpp>
#include "Engine/Math/BoundingBox.h"
#include <glm/common.hpp>
struct Sphere {
	glm::vec3 position;
	float radius;
	inline Sphere() {
		position = glm::vec3();
		radius = 1.0f;
	}
	inline Sphere(glm::vec3 position_, float radius_) {
		position = position_;
		radius = radius_;
	}
	bool Intersects(BoundingBox bb);
};
#endif