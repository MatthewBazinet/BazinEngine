#ifndef HURTBOX_H
#define HURTBOX_H

#include "Sphere.h"
#include <iostream>
#include <vector>

#include "Engine/Core/CoreEngine.h"
#include "HurtBoxVisual.h"
class GameObject;
class Model;
class Camera;
class HurtBox:public GameObject
{
	friend class HitBox;
public:
	HurtBox(Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), GameObject* parent_ = nullptr, float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat orientation_ = glm::quat(0.0f, 5.0f, 5.0f, 5.0f), glm::quat angularVelocity_ = glm::quat());
	~HurtBox();
	void Update(const float deltaTime_) override;
	

	glm::vec3 GetPosition() { return position; };
	std::vector<Sphere> SpawnHurtBox(Model* model_, glm::vec3 startingPos_, glm::vec3 endingPos_, float width_, int numOfSpheres);
	float GetRadius() { return radius; };
	std::vector<Sphere> GetHurtBoxes()const;
	void SetPosition(glm::vec3 position_);
	glm::vec3 GetPointOnLine(glm::vec3 x, glm::vec3 y, float normalizedDistance);
private:
	float radius;
	GameObject* parent;
	std::vector<GameObject*> hurtBoxVisual;
	std::vector<Sphere> hurtBoxes;
};
#endif
