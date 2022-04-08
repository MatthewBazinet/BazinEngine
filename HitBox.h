#ifndef HITBOX_H
#define HITBOX_H
#include "Engine/Math/BoundingBox.h"
#include "Sphere.h"
#include <iostream>
#include <vector>
#include "Component.h"
#include "HurtBox.h"
#include "HurtBoxVisual.h"
#include "Engine/Rendering/3D/GameObject.h"

class HitBox : public GameObject
{
public:
	HitBox(Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), GameObject* parent_ = nullptr, float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat orientation_ = glm::quat(0.0f, 5.0f, 5.0f, 5.0f), glm::quat angularVelocity_ = glm::quat());
	HitBox(GameObject* parent_);
	~HitBox();
	void Update(const float deltaTime_);

	void SpawnBoundingBox();
	bool CheckCollision(HitBox* hitbox);
	bool CheckCollision(std::vector<Sphere> hurtbox);
	std::vector<Sphere> spawnSpheres(glm::vec3 startingPos_, glm::vec3 endingPos_, float width_, int numOfSpheres);
	glm::vec3 GetPointOnLine(glm::vec3 x, glm::vec3 y, float normalizedDistance);

	glm::vec3 getMaxVert() { return maxVert; };
	glm::vec3 getMinVert() { return minVert; };
	glm::vec3 GetPosition() { return position; };
	float GetRadius() { return radius; }
	std::vector<Sphere> GetSpheres() {return spheres;};
	bool GetIsEnabled() { return isEnabled; };

	void DisableHitBox() { isEnabled = false; };
	void EnableHitBox() { isEnabled = true; };
	void setMaxVert(glm::vec3 maxVert_) { maxVert = maxVert_; };
	void setMinVert(glm::vec3 minVert_) { minVert = minVert_; };
private:
	glm::vec3 maxVert, minVert;
	glm::mat4 transform;
	glm::vec3 position;
	float radius;
	GameObject* parent;
	std::vector<Sphere> spheres;
	bool isEnabled;
	//std::vector<GameObject*> hitBoxVisual;
	std::vector<Sphere> hitBoxes;
};

#endif