#include "Sphere.h"

bool Sphere::Intersects(BoundingBox bb)
{
	float x = glm::max(bb.minVert.x, glm::min(this->position.x, bb.maxVert.x));
	float y = glm::max(bb.minVert.y, glm::min(this->position.y, bb.maxVert.y));
	float z = glm::max(bb.minVert.z, glm::min(this->position.z, bb.maxVert.z));
	float distance = glm::sqrt((x - this->position.x) * (x - this->position.x) + (y - this->position.y) * (y - this->position.y) + (z - this->position.z) * (z - this->position.z));

	return distance < this->radius;
}
