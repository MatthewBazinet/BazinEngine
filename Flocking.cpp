#include "Flocking.h"

Flocking::Flocking(Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : GameObject(model_, position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_)
{
	target = nullptr;
}
void Flocking::Update(const float deltaTime_)
{

	if (target) {
		//SteeringOutput kin = MatchVelocity::getSteering(this, target, 0.5f, glm::vec3(5.0f));
		SteeringOutput kin = MatchVelocity::getSteering(this, target, 2.0f, glm::vec3(1.0f));

		SetVelocity(kin.linear);
		SetAngle(kin.angular);
		
	}
	GameObject::Update(deltaTime_);
}
Flocking::~Flocking()
{
}
