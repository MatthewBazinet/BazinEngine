#include "HurtBox.h"
#include "Game\Character.h"
HurtBox::HurtBox()
{

}

HurtBox::HurtBox(GameObject* parent_)
{
	parent = parent_;
}


HurtBox::~HurtBox()
{
}

void HurtBox::Update(const float deltaTime_)
{
	for (int i = 0; i < hurtBoxes.size(); i++) {
		hurtBoxes[i].position = parent->GetPosition();
		//std::cout << hitBoxes[i].position.x << "," << hitBoxes[i].position.y << "," << hitBoxes[i].position.z << std::endl;
	}
}

std::vector<Sphere> HurtBox::SpawnHurtBox(glm::vec3 startingPos_, glm::vec3 endingPos_, float width_, int numOfSpheres)
{
	if (numOfSpheres >= 2) {
		spheres.resize(2 + numOfSpheres);
		float dist = glm::distance(startingPos_, endingPos_);
		float spacing = dist / numOfSpheres;

		for (int i = 0; i < spheres.size(); i++) {
			glm::vec3 pos = GetPointOnLine(startingPos_, endingPos_, i * spacing / dist);
			spheres[i] = Sphere(pos, width_);
			hurtBoxes.push_back(spheres[i]);
			std::cout << hurtBoxes[i].position.x << "," << hurtBoxes[i].position.y << "," << hurtBoxes[i].position.z << std::endl;
		}
	}
	else {
		spheres.resize(numOfSpheres);
		spheres[0] = Sphere(startingPos_, width_);
		hurtBoxes.push_back(spheres[0]);
		std::cout << hurtBoxes[0].position.x << "," << hurtBoxes[0].position.y << "," << hurtBoxes[0].position.z << std::endl;
	}
	return hurtBoxes;
}

void HurtBox::SetPosition()
{
}

glm::vec3 HurtBox::GetPointOnLine(glm::vec3 x, glm::vec3 y, float normalizedDistance)
{
	return x + (y - x) * normalizedDistance;
}


