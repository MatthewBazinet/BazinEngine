#include "Pawn.h"

Pawn::Pawn(Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : GameObject(model_, position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_)
{
	
}

Pawn::~Pawn()
{
}

void Pawn::Update(const float deltaTime_)
{
	
	KinematicChainArrive::getSteering(this, target, 1.0f);
	KinematicChainArrive::LookAt(glm::vec3(100.0f));
	GameObject::Update(deltaTime_);
}
