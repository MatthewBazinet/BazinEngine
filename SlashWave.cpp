#include "SlashWave.h"
#include "../Game/Characters/Wulfrun.h"

SlashWave::SlashWave(FrameData frameData_, float lifeTime_, glm::vec3 position_, Character* parent_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) : Projectile(new Model("Resources/Models/SlashWave.obj", "Resources/Materials/SlashWave.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), position_, parent_, angle_, rotation_)
{
	frameData = frameData_;
	lifeTime = lifeTime_;
	time = 0.0f;
}

SlashWave::~SlashWave()
{
	Projectile::~Projectile();
}

void SlashWave::Update(const float deltaTime_)
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