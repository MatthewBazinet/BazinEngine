#include "NightGaunt.h"
#include "../Game/Characters/Eldric.h"

NightGaunt::NightGaunt(FrameData frameData_, glm::vec3 position_, Character* parent_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) : Projectile(new Model("Resources/Models/NightGaunt.obj", "Resources/Materials/NightGaunt.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), position_, parent_, angle_, rotation_, scale_)
{
	SceneGraph::GetInstance()->AddModel(model);
	frameData = frameData_;
	target = parent->GetOpponent();
}

NightGaunt::~NightGaunt()
{
	SceneGraph::GetInstance()->RemoveModel(model);
	Projectile::~Projectile();
}

void NightGaunt::Update(const float deltaTime_)
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

				NightGaunt::~NightGaunt();
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