#include "GravityWave.h"
#include "../Game/Characters/Hoshi.h"

GravityWave::GravityWave(FrameData frameData_, glm::vec3 position_, Character* parent_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) : Projectile(new Model("Resources/Models/Kunai.obj", "Resources/Materials/Kunai.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), position_, parent_, angle_, rotation_)
{
	frameData = frameData_;
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
			if (hitBox->CheckCollision(parent->GetOpponent()->GetHurtBoxes()))
			{
				parent->GetOpponent()->Hit(frameData);
				parent->GetOpponent()->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
				//parent->GetOpponent()->SetPosition(glm::vec3(parent->GetOpponent()->GetPosition().x, 4.0f, parent->GetOpponent()->GetPosition().z));
				parent->GetOpponent()->setApplyGravity(false);

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
