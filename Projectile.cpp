#include "Projectile.h"

Projectile::Projectile(Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : GameObject(model_, position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_)
{
	
	SetMaxSpeed(2.0f);
}

Projectile::~Projectile()
{
}

void Projectile::LookAt(glm::vec3 velocity)
{
	angle = atan2(rotation.x, rotation.z); // Note: I expected atan2(z,x) but OP reported success with atan2(x,z) instead! Switch around if you see 90° off.
	velocity.x = 0.0f;
	velocity.y = 1 * sin(angle / 2);
	velocity.z = 0.0f;
}
