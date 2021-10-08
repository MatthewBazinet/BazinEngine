#include "AICharacter.h"
#include <glm/gtx/rotate_vector.hpp>
#include "Engine/Math/CollisionDetection.h"
#include "Engine/Math/Ray.h"

AICharacter::AICharacter(GameObject* opponent_, float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : Character(health_, meter_, isRunning_, isAirborne_, model_,  position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_) {
	opponent = static_cast<Character*>(opponent_);
	SetMaxSpeed(3.0f);
	targetShifted = false;
}

void AICharacter::Update(const float deltaTime_)
{
	// target = opponent->GetPosition() + -maxSpeed * glm::rotate(glm::vec3(1.0f, 0.0f, 0.0f), opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));

	if (getIsAirborne())
	{
		ApplyForce(glm::vec3(accel.x, -9.81f * mass, accel.z));
	}

	Ray ray = Ray();
	ray.direction = vel;
	ray.origin = position;
	CollisionDetection::RayObbIntersection(&ray, &opponent->GetBoundingBox());

	if (ray.intersectionDist < maxSpeed/deltaTime_)
	{
		target += glm::cross(ray.direction, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	if (opponent->GetPosition().x - GetPosition().x > -3.0f && opponent->GetPosition().x - GetPosition().x < 3.0f)
	{
		if (getIsAirborne() == false)
		{
			SetVelocity(glm::vec3(GetVelocity().x, 7.0f, GetVelocity().z));
		}
	}

	// KinematicSteeringOutput steering = KinematicSeek::getSteering(this, target);
	// KinematicSteeringOutput steering = KinematicFlee::getSteering(this, target);
	KinematicSteeringOutput steering = KinematicArrive::getSteering(this, glm::vec3(-10.0f, 0.0f, 0.0f), 2.5f);
	vel = glm::vec3(steering.velocity.x, GetVelocity().y, steering.velocity.z);
	angle = steering.rotation;
	Character::Update(deltaTime_);
}