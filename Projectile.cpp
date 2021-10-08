#include "Projectile.h"



Projectile::Projectile(Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : GameObject(model_, position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_)
{
	target = nullptr;//glm::vec3(0.0f, 0.0f, 0.0f);
	
	SetMaxSpeed(2.0f);
}

Projectile::~Projectile()
{
}

void Projectile::Update(const float deltaTime_)
{
	KinematicSteeringOutput kin = KinematicSeek::getSteering(this, target->GetPosition());
	kin.velocity.y = 0.0f;
	SetVelocity(kin.velocity);
	SetAngle(kin.rotation);
	
	GameObject::Update(deltaTime_);
}

