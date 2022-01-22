#ifndef HITBOX_H
#define HITBOX_H
#include "Engine/Math/BoundingBox.h"
#include <iostream>

class HitBox
{
public:
	HitBox();
	~HitBox();
	void SpawnBoundingBox();
	bool CheckCollision(HitBox* hitbox);

	glm::vec3 getMaxVert() { return maxVert; };
	glm::vec3 getMinVert() { return minVert; };
	void setMaxVert(glm::vec3 maxVert_) { maxVert = maxVert_; };
	void setMinVert(glm::vec3 minVert_) { minVert = minVert_; };

private:
	glm::vec3 maxVert, minVert;
	glm::mat4 transform;
};

#endif