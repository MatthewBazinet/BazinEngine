#include "Pawn.h"

Pawn::Pawn(Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : GameObject(model_, position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_)
{
	SetMaxSpeed(1000.0f);
}

Pawn::~Pawn()
{
}

void Pawn::Update(const float deltaTime_)
{
	KinematicSteeringOutput kin = KinematicChainArrive::getSteering(this, target, 1.5f);
	SetVelocity(kin.velocity);
	SetAngle(kin.rotation);
	GameObject::Update(deltaTime_);
}
