#include "Spike.h"

#include "../Game/Characters/Eldric.h"

Spike::Spike(FrameData frameData_, glm::vec3 position_, Character* parent_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) : Projectile(new Model("Resources/Models/Spike.obj", "Resources/Materials/Spike.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), position_, parent_, angle_, rotation_, scale_)
{
	SceneGraph::GetInstance()->AddModel(model);
	frameData = frameData_;
	active = false;
	lifetime = 5.0f;
	time = 0.0f;
}

Spike::~Spike()
{
	SceneGraph::GetInstance()->RemoveModel(model);
	Projectile::~Projectile();
}

void Spike::Update(const float deltaTime_)
{
	if (parent) {
		if (parent->GetOpponent()) {
			if (active)
			{
				time += deltaTime_;

				if (hitBox->CheckCollision(parent->GetOpponent()->GetHurtBoxes()))
				{
					parent->GetOpponent()->Hit(frameData);

					Spike::~Spike();
					dynamic_cast<Eldric*>(parent)->ResetProjectile();
					return;
				}
				else if (time > lifetime)
				{
					Spike::~Spike();
					dynamic_cast<Eldric*>(parent)->ResetProjectile();
					return;
				}
			}
		}
	}

	if (this)
	{
		hitBox->Update(deltaTime_);
		GameObject::Update(deltaTime_);
	}
}