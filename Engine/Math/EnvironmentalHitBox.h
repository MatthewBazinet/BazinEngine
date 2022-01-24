#ifndef ENVIRONMENTALHITBOX_H
#define ENVIRONMENTALHITBOX_H

#include "BoundingBox.h"

class EnvironmentalHitBox : public BoundingBox
{
public:
	EnvironmentalHitBox();

	glm::vec3 getMaxVert() { return maxVert; };
	glm::vec3 getMinVert() { return minVert; };
	void setMaxVert(glm::vec3 maxVert_) { maxVert = maxVert_; };
	void setMinVert(glm::vec3 minVert_) { minVert = minVert_; };
};

#endif;