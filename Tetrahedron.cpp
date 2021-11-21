#include "Tetrahedron.h"

void Tetrahedron::Update()
{
	for (int i = 0; i < NUM_OF_TETRAHEDRON_POINTS; i++)
	{
		transformedPoints[i] = (points[i] * rotation) + centre;
	}
}

glm::vec3 Tetrahedron::Support(glm::vec3 direction)
{
	float dotMax = FLT_MIN;
	glm::vec3 result;
	for (int i = 0; i < NUM_OF_TETRAHEDRON_POINTS; i++)
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
