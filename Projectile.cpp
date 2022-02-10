#include "Projectile.h"

Projectile::Projectile(Model* model_, glm::vec3 position_, Character* parent_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : GameObject(model_, position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_)
{
	target = nullptr;//glm::vec3(0.0f, 0.0f, 0.0f);
	SetMaxSpeed(3.0f);
	parent = parent_;
	hitBox = HitBox(this);
	hitBox.spawnSpheres(this->GetPosition(), this->GetPosition(), 1.0f, 1);
}

Projectile::~Projectile()
{
}

void Projectile::Separate(std::vector<GameObject*> objects_)
{
	float dist;
	glm::vec3 direction;
	for (auto tmp : objects_) {
		if (this != tmp) {
			dist = glm::distance(tmp->GetPosition(), this->GetPosition());
			if (dist < 10.0f) {
				direction = tmp->GetPosition() - this->GetPosition();
				glm::normalize(direction);
				float strength = 2.0f * (10.0f - dist) / 2.0f;
				tmp->SetVelocity(strength * direction);
			}
		}
	}
}

void Projectile::Update(const float deltaTime_)
{
	if (target) 
	{
		KinematicSteeringOutput kin = KinematicSeek::getSteering(this, target->GetPosition());
		kin.velocity.y = 0.0f;
		SetVelocity(kin.velocity);
		SetAngle(kin.rotation);
	}

	hitBox.Update(deltaTime_);
		if (parent) {
			if (parent->GetOpponent()) {
				if (hitBox.CheckCollision(parent->GetOpponent()->GetHurtBoxes())) {
					std::cout << "collided" << std::endl;
				}
			}
		}

	GameObject::Update(deltaTime_);
}

