#ifndef FLOCKING_H
#define FLOCKING_H
#include "Engine/Rendering/3D/GameObject.h"
#include "MatchVelocity.h"
class Flocking : public GameObject
{
public:
	void Update(const float deltaTime_) override;
	Flocking(Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat orientation_ = glm::quat(0.0f, 5.0f, 5.0f, 5.0f), glm::quat angularVelocity_ = glm::quat());
	~Flocking();
	void SetTarget(GameObject* target_) { target = target_; };
private:
	GameObject* target;
	
};
#endif