#include "GravityWave.h"
#include "../Game/Characters/Hoshi.h"

GravityWave::GravityWave(glm::vec3 position_, Character* parent_, int strength_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) : Projectile(new Model("Resources/Models/Kunai.obj", "Resources/Materials/Kunai.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), position_, parent_, angle_, rotation_)
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
					parent->GetOpponent()->Hit(10.0f, 0.5f, 0.25f, glm::vec3(0.0f, 0.0f, 0.0f));
					parent->GetOpponent()->ApplyForce((parent->GetOpponent()->GetPosition() - parent->GetPosition()) * 100.0f);
				}
				else if (strength == 1)
				{
					parent->GetOpponent()->Hit(10.0f, 0.5f, 0.25f, glm::vec3(0.0f, 0.0f, 0.0f));
					parent->GetOpponent()->ApplyForce(glm::vec3(0.0f, 100.0f, 0.0f));
				}
				else if (strength == 2)
				{
					parent->GetOpponent()->Hit(10.0f, 0.5f, 0.25f, glm::vec3(0.0f, 0.0f, 0.0f));
					parent->GetOpponent()->ApplyForce(glm::vec3(0.0f, 100.0f, 0.0f));
					//parent->GetOpponent()->setApplyGravity(false);
				}

				GravityWave::~GravityWave();
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
