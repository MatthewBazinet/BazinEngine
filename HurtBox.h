#ifndef HURTBOX_H
#define HURTBOX_H

#include "Component.h"
#include "Sphere.h"
#include <iostream>
#include <vector>
class HurtBox
{
	friend class HitBox;
public:
	HurtBox();
	~HurtBox();
	glm::vec3 GetPosition() { return position; };
	void SpawnHurtBox(glm::vec3 startingPos_, glm::vec3 endingPos_, float width_, int numOfSpheres);
	float GetRadius() { return radius; };
	void SetPosition();
	
private:
	float radius;
	glm::vec3 position;
	std::vector<Sphere> spheres;
};
#endif
