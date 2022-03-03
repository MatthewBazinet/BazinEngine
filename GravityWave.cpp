#include "GravityWave.h"

GravityWave::GravityWave(Model* model_, glm::vec3 position_, Character* parent_, int strength_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) : Projectile(model_, position_, parent_, angle_, rotation_)
{
	strength = strength_;
}

GravityWave::~GravityWave()
{
	Projectile::~Projectile();
}

void GravityWave::Update(float deltaTime_)
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
				if (strength == 0)
				{
					parent->GetOpponent()->SetVelocity(glm::vec3(10.0f, 00.0f, 0.0f));
				}
				else if (strength == 1)
				{
					parent->GetOpponent()->SetVelocity(glm::vec3(0.0f, 10.0f, 0.0f));
				}
				else if (strength == 2)
				{

				}
			}
		}
	}
	hitBox->Update(deltaTime_);
	GameObject::Update(deltaTime_);
}
