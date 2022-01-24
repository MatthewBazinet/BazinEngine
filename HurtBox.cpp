#include "HurtBox.h"

HurtBox::HurtBox()
{
}

HurtBox::~HurtBox()
{
}

void HurtBox::SpawnHurtBox(glm::vec3 startingPos_, glm::vec3 endingPos_, float width_, int numOfSpheres)
{
	spheres.resize(2 + numOfSpheres);
	float dist = glm::distance(startingPos_, endingPos_);
	float spacing = dist / numOfSpheres;

	for (int i = 0; i < spheres.size(); i++) {
		//glm::vec3 pos = GetPointOnLine(startingPos_, endingPos_, i * spacing / dist);
		//hitBoxes.push_back(spheres[i]);
		//spheres[i] = new Sphere(pos, width_);
	}
}

void HurtBox::SetPosition()
{
}


