#include "Spike.h"

#include "../Game/Characters/Eldric.h"

Spike::Spike(FrameData frameData_, glm::vec3 position_, Character* parent_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) : Projectile(new Model("Resources/Models/Spike.obj", "Resources/Materials/Spike.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), position_, parent_, angle_, rotation_, scale_)
{
	frameData = frameData_;
	active = false;
	lifetime = 5.0f;
	time = 0.0f;
	modelLoaded = false;
}

Spike::~Spike()
{
	active = false;
	SceneGraph::GetInstance()->RemoveModel(model);
}

void Spike::Update(const float deltaTime_)
{
	if (parent) {
		if (parent->GetOpponent()) {
			if (active)
			{
				if (!modelLoaded)
				{
					SceneGraph::GetInstance()->AddModel(model);
					modelLoaded = true;
				}
				time += deltaTime_;

				if (hitBox->CheckCollision(parent->GetOpponent()->GetHurtBoxes()))
				{
					parent->GetOpponent()->Hit(frameData);

					dynamic_cast<Eldric*>(parent)->ResetProjectile();
					return;
				}
				else if (time > lifetime)
				{
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