#include "HitBox.h"

HitBox::HitBox()
{

}

HitBox::HitBox(GameObject* parent_)
{
	parent = parent_;

}

HitBox::~HitBox()
{
}

void HitBox::SpawnBoundingBox()
{
}

bool HitBox::CheckCollision(HitBox* hitbox)
{
	if ((this->minVert.x <= hitbox->maxVert.x && this->maxVert.x >= hitbox->minVert.x) && (this->minVert.y <= hitbox->maxVert.y && this->maxVert.y >= hitbox->minVert.y) && (this->minVert.z <= hitbox->maxVert.z && this->maxVert.z >= hitbox->minVert.z))
	{
		//std::cout << "collided" << std::endl;
		return true;
	}
	return false;
}

bool HitBox::CheckCollision(std::vector<HurtBox*> hurtbox)
{
	for (auto tmp : hurtbox) {
		for (int i = 0; i < hitBoxes.size(); i++) {
			float distance = glm::sqrt((hitBoxes[i]->position.x - tmp->GetPosition().x) * (hitBoxes[i]->position.x - tmp->GetPosition().x) +
				(hitBoxes[i]->position.y - tmp->GetPosition().y) * (hitBoxes[i]->position.y - tmp->GetPosition().y) +
				(hitBoxes[i]->position.z - tmp->GetPosition().z) * (hitBoxes[i]->position.z - tmp->GetPosition().z));
			return distance < (hitBoxes[i]->radius + tmp->GetRadius());
		}
	}
}

void HitBox::spawnSpheres(glm::vec3 startingPos_, glm::vec3 endingPos_, float width_, int numOfSpheres)
{
	if (numOfSpheres >= 2) {
		spheres.resize(2 + numOfSpheres);
		float dist = glm::distance(startingPos_, endingPos_);
		float spacing = dist / numOfSpheres;

		for (int i = 0; i < spheres.size(); i++) {
			glm::vec3 pos = GetPointOnLine(startingPos_, endingPos_, i * spacing / dist);
			spheres[i] = new Sphere(pos, width_);
			hitBoxes.push_back(spheres[i]);
			std::cout << hitBoxes[i]->position.x<< "," << hitBoxes[i]->position.y <<","<< hitBoxes[i]->position.z << std::endl;
		}
	}
	else {
		spheres.resize(numOfSpheres);
		spheres[0] = new Sphere(startingPos_, width_);
		hitBoxes.push_back(spheres[0]);
		std::cout << hitBoxes[0]->position.x << "," << hitBoxes[0]->position.y << "," << hitBoxes[0]->position.z << std::endl;
	}


}
glm::vec3 HitBox::GetPointOnLine(glm::vec3 x, glm::vec3 y, float normalizedDistance)
{
	return x + (y - x) * normalizedDistance;
}
void HitBox::Update(float deltaTime_)
{
	for (auto tmp : hitBoxes) {
		tmp->position = parent->GetPosition();
	}
}
