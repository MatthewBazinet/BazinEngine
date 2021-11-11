#ifndef PAWN_H
#define PAWN_H

#include "Engine/Rendering/3D/GameObject.h"
#include "KinematicChainArrive.h"
class Pawn : 
	public GameObject
{
public:
	Pawn(Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat orientation_ = glm::quat(0.0f, 5.0f, 5.0f, 5.0f), glm::quat angularVelocity_ = glm::quat());
	~Pawn();
	void SetTarget(glm::vec3 target_) { target.push_back(target_); };
	void Update(const float deltaTime_) override;
private:
	std::vector<glm::vec3> target;
};
#endif
