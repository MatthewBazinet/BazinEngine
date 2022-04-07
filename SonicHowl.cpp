#include "SonicHowl.h"
#include "../Game/Characters/Wulfrun.h"

SonicHowl::SonicHowl(FrameData frameData_, float lifeTime_, glm::vec3 position_, Character* parent_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) : Projectile(new Model("Resources/Models/SonicHowl.obj", "Resources/Materials/SonicHowl.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), position_, parent_, angle_, rotation_)
{
	frameData = frameData_;
	lifeTime = lifeTime_;
	time = 0.0f;
}

SonicHowl::~SonicHowl()
{
	Projectile::~Projectile();
}

void SonicHowl::Update(const float deltaTime_)
{
	time += deltaTime_;
	if (time > lifeTime || position.y < 0.1f)
	{
		dynamic_cast<Wulfrun*>(parent)->RemoveProjectile(GetTag());
		return;
	}

	if (parent) {
		if (parent->GetOpponent()) {
			if (hitBox->CheckCollision(parent->GetOpponent()->GetHurtBoxes())) {
				//std::cout << "collided" << std::endl;
				parent->GetOpponent()->Hit(frameData);
				dynamic_cast<Wulfrun*>(parent)->RemoveProjectile(GetTag());
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