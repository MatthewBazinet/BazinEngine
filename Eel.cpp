#include "Eel.h"
#include "../Game/Characters/Eldric.h"

Eel::Eel(FrameData frameData_, glm::vec3 position_, Character* parent_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) : Projectile(new Model("Resources/Models/Eel.obj", "Resources/Materials/Eel.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), position_, parent_, angle_, rotation_, scale_)
{
	SceneGraph::GetInstance()->AddModel(model);
	frameData = frameData_;
}

Eel::~Eel()
{
	SceneGraph::GetInstance()->RemoveModel(model);
	Projectile::~Projectile();
}

void Eel::Update(const float deltaTime_)
{
	if (position.y > 0.1f)
	{
		ApplyForce(glm::vec3(accel.x, -9.81f * mass, accel.z));
	}
	else
	{
		Eel::~Eel();
		dynamic_cast<Eldric*>(parent)->RemoveProjectile(tag);
		return;
	}


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

				Eel::~Eel();
				dynamic_cast<Eldric*>(parent)->ResetProjectile();
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
