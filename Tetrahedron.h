#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#define NUM_OF_TETRAHEDRON_POINTS 4

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct Tetrahedron
{
public:
	glm::vec3 centre;

	glm::quat rotation;

	glm::vec3 points[NUM_OF_TETRAHEDRON_POINTS];

	glm::vec3 transformedPoints[NUM_OF_TETRAHEDRON_POINTS];

	void Update();

	glm::vec3 Support(glm::vec3 direction);
};

#endif // !TETRAHEDRON_H