#ifndef HURTBOX_H
#define HURTBOX_H

#include "Sphere.h"
#include <iostream>
#include <vector>

class Character;
class GameObject;
class HurtBox
{
	friend class HitBox;
public:
	HurtBox();
	HurtBox(GameObject* parent_);
	~HurtBox();
	void Update(const float deltaTime_);
	glm::vec3 GetPosition() { return position; };
	std::vector<Sphere> SpawnHurtBox(glm::vec3 startingPos_, glm::vec3 endingPos_, float width_, int numOfSpheres);
	float GetRadius() { return radius; };
	std::vector<Sphere> GetHurtBoxes()const { return hurtBoxes; };
	void SetPosition();
	glm::vec3 GetPointOnLine(glm::vec3 x, glm::vec3 y, float normalizedDistance);
private:
	float radius;
	GameObject* parent;
	glm::vec3 position;
	std::vector<Sphere> spheres;
	std::vector<Sphere> hurtBoxes;
	
};
#endif
