#include "Tetrahedron.h"

void Tetrahedron::Update()
{
	for (int i = 0; i < NUM_OF_TETRAHEDRON_POINTS; i++)
	{
		transformedPoints[i] = (points[i] * rotation) + centre; //rotate then translate all the points
	}
}

//Gets the point furthest in the given direction
glm::vec3 Tetrahedron::Support(glm::vec3 direction)
{
	float dotMax = glm::dot(transformedPoints[0], direction);
	glm::vec3 result = transformedPoints[0];
	for (int i = 1; i < NUM_OF_TETRAHEDRON_POINTS; i++)
	{
		float dot = glm::dot(transformedPoints[i], direction);
		
		if (dot > dotMax)
		{
			dotMax = dot;
			result = transformedPoints[i];
		}
	}
	return result;
}
