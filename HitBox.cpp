#include "HitBox.h"

HitBox::HitBox()
{
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
		std::cout << "collided" << std::endl;
		return true;
	}
	return false;
}
