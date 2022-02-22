#include "HitBox.h"
#include "Engine/Math/CollisionDetection.h"
HitBox::HitBox()
{

}

HitBox::HitBox(GameObject* parent_)
{
	parent = parent_;
	isEnabled = true;
	int j = 0;
}

HitBox::~HitBox()
{
}

void HitBox::SpawnBoundingBox()
{
}

bool HitBox::CheckCollision(HitBox* hitbox)
{
	if (isEnabled) {
		if ((this->minVert.x <= hitbox->maxVert.x && this->maxVert.x >= hitbox->minVert.x) && (this->minVert.y <= hitbox->maxVert.y && this->maxVert.y >= hitbox->minVert.y) && (this->minVert.z <= hitbox->maxVert.z && this->maxVert.z >= hitbox->minVert.z))
		{
			//std::cout << "collided" << std::endl;
			return true;
		}
	}

	return false;
}

bool HitBox::CheckCollision(std::vector<Sphere> hurtbox)
{
	if (isEnabled) {
		for (int i = 0; i < hurtbox.size(); i++) {
			for (int j = 0; j < hitBoxes.size(); j++) {
				return CollisionDetection::SphereSphereCollision(hurtbox[i], hitBoxes[j]);
			}
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
			spheres[i] = Sphere(pos, width_);
			hitBoxes.push_back(spheres[i]);
			std::cout << hitBoxes[i].position.x<< "," << hitBoxes[i].position.y <<","<< hitBoxes[i].position.z << std::endl;
		}
	}
	else {
		spheres.resize(numOfSpheres);
		spheres[0] = Sphere(startingPos_, width_);
		hitBoxes.push_back(spheres[0]);
		std::cout << hitBoxes[0].position.x << "," << hitBoxes[0].position.y << "," << hitBoxes[0].position.z << std::endl;
	}


}
glm::vec3 HitBox::GetPointOnLine(glm::vec3 x, glm::vec3 y, float normalizedDistance)
{
	return x + (y - x) * normalizedDistance;
}
void HitBox::Update(float deltaTime_)
{
	for (int i = 0; i < hitBoxes.size(); i++) {
		hitBoxes[i].position = parent->GetPosition();
		//std::cout << hitBoxes[i].position.x << "," << hitBoxes[i].position.y << "," << hitBoxes[i].position.z << std::endl;
	}
}
