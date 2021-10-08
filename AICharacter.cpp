#include "AICharacter.h"
#include <glm/gtx/rotate_vector.hpp>
#include "Engine/Math/CollisionDetection.h"
#include "Engine/Math/Ray.h"

AICharacter::AICharacter(Character* opponent_, float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : Character(health_, meter_, isRunning_, isAirborne_, model_,  position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_) {
	opponent = opponent_;
	SetMaxSpeed(7.0f);
	targetShifted = false;
	projectile = nullptr;
}

void AICharacter::Update(const float deltaTime_)
{
	KinematicSteeringOutput steering;

	if (getIsAirborne())
	{
		ApplyForce(glm::vec3(accel.x, -9.81f * mass, accel.z));
	}

	target = opponent->GetPosition() + -maxSpeed * glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));

	Ray ray = Ray();
	ray.direction = vel;
	ray.origin = position;
	BoundingBox tmp = opponent->GetBoundingBox();
	CollisionDetection::RayObbIntersection(&ray, &tmp);
	
	
	if (ray.intersectionDist < maxSpeed / deltaTime_)
	{
		target += glm::cross(ray.direction, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	steering = KinematicArrive::getSteering(this, target, 1.5f);
	float preserveY = vel.y;
	vel = steering.velocity;
	vel.y = preserveY;

	if (projectile != nullptr)
	{
		target = projectile->GetPosition();


		if (glm::distance(position, projectile->GetPosition()) < 3.0f)
		{
			steering = KinematicFlee::getSteering(this, projectile->GetPosition());
			float preserveY = vel.y;
			vel = steering.velocity;
			vel.y = preserveY;

		}

		if (glm::distance(position, projectile->GetPosition()) < 5.0f)
		{
			if (getIsAirborne() == false)
			{
				SetVelocity(glm::vec3(GetVelocity().x, 10.0f, GetVelocity().z));
			}
		}
		
	}


	
	angle = steering.rotation;
	Character::Update(deltaTime_);
}