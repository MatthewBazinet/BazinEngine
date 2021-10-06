#pragma once
#include "Engine/Math/BoundingBox.h"
class HitBox
{
public:
	HitBox();
	~HitBox();
	void SpawnBoundingBox();
	glm::vec3 maxVert, minVert;
	glm::mat4 transform;

private:
};

