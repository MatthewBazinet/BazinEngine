#include "Kunai.h"
#include "../Game/Characters/Hoshi.h"

Kunai::Kunai(Model* model_, glm::vec3 position_, Character* parent_, float angle_, glm::vec3 rotation_ , glm::vec3 scale_) : Projectile(model_, position_, parent_, angle_, rotation_)
{
	
}

Kunai::~Kunai()
{
	Projectile::~Projectile();
}

void Kunai::Update(const float deltaTime_)
{
	if (target)
	{
		KinematicSteeringOutput kin = KinematicSeek::getSteering(this, target->GetPosition());
		kin.velocity.y = 0.0f;
		SetVelocity(kin.velocity);
		SetAngle(kin.rotation);
	}


	if (parent) {
		if (parent->GetOpponent()) {
			if (hitBox->CheckCollision(parent->GetOpponent()->GetHurtBoxes())) {
				std::cout << "collided" << std::endl;
				parent->GetOpponent()->SetVelocity(parent->GetPosition() - parent->GetOpponent()->GetPosition());
				dynamic_cast<Hoshi*>(parent)->ResetProjectile();
				return;
			}
		}
	}

	if (this)
	{
		hitBox->Update(deltaTime_);
		GameObject::Update(deltaTime_);
	}
}