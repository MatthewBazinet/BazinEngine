#include "AICharacter.h"
#include <glm/gtx/rotate_vector.hpp>
#include "Engine/Math/CollisionDetection.h"
#include "Engine/Math/Ray.h"

AICharacter::AICharacter(Character* opponent_, float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : Character(health_, meter_, isRunning_, isAirborne_, model_,  position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_) {
	opponent = opponent_;
	SetMaxSpeed(7.0f);
	targetShifted = false;
	projectile = nullptr;
	dir2D = 1.0f;
}

void AICharacter::Update(const float deltaTime_)
{

	if (getIsAirborne())
	{
		ApplyForce(glm::vec3(accel.x, -9.81f * mass, accel.z));
	}

	if (isRunning)
	{
		KinematicSteeringOutput steering;

		

		target = opponent->GetPosition() + -maxSpeed * glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));

		Ray ray = Ray();
		ray.direction = vel;
		ray.origin = position;
		CollisionDetection::RayObbIntersection(&ray, &(opponent->GetBoundingBox()));
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
	}
	else
	{
		if (!opponent->getIsRunning() && getIsAirborne() == false)
		{
			axisOf2DMovement = glm::abs(glm::normalize(opponent->GetPosition() - position));
		}
		float preserveY = vel.y;
		vel = axisOf2DMovement * maxSpeed * dir2D;
		vel.y = preserveY;
		if (projectile) {
			if (glm::distance(position, projectile->GetPosition()) < 5.0f)
			{
				if (getIsAirborne() == false)
				{
					SetVelocity(glm::vec3(GetVelocity().x, 10.0f, GetVelocity().z));
					isAirborne = true;
				}
			}
		}

		if (glm::distance(position, opponent->GetPosition()) < 5.0f)
		{
			if (getIsAirborne() == false)
			{
				SetVelocity(glm::vec3(GetVelocity().x, 10.0f, GetVelocity().z));
				isAirborne = true;
			}
		}

	}
	Character::Update(deltaTime_);
}

void AICharacter::SetDir2D(float dir_)
{
	if (abs(dir_) > 0.0f || abs(dir_) < 1.0f)
	{
		if (dir_ == 0.0f)
		{
			dir2D = 0.0f;
		}
		else
		{
			dir2D = (dir_ > 0.0f) ? 1.0f : -1.0f;
		}
	}
	else
	{
		dir2D = dir_;
	}
}
