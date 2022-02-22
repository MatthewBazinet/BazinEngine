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
	if (this) {
		if (parent) {
			parent = nullptr;
		}
	}
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
		float dist = glm::distance(startingPos_, endingPos_);
		float spacing = dist / numOfSpheres;

		for (int i = 0; i < numOfSpheres; i++) {
			glm::vec3 pos = GetPointOnLine(startingPos_, endingPos_, i * spacing / dist);
			hurtBoxes.push_back(Sphere(pos, width_));
			std::cout << hurtBoxes[i].position.x << "," << hurtBoxes[i].position.y << "," << hurtBoxes[i].position.z << std::endl;
		}
	}
	else {
		hurtBoxes.push_back(Sphere(startingPos_, width_));
		std::cout << hurtBoxes[0].position.x << "," << hurtBoxes[0].position.y << "," << hurtBoxes[0].position.z << std::endl;
	}

	return hurtBoxes;
}

std::vector<Sphere> HurtBox::GetHurtBoxes() const
{
	if (hurtBoxes.size() > 0) {
		return hurtBoxes;
	}
	return std::vector<Sphere>();
}

void HurtBox::SetPosition()
{
}

glm::vec3 HurtBox::GetPointOnLine(glm::vec3 x, glm::vec3 y, float normalizedDistance)
{
	return x + (y - x) * normalizedDistance;
}


