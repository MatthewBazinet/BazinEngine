#include "AICharacter.h"
#include <glm/gtx/rotate_vector.hpp>
#include "Engine/Math/CollisionDetection.h"
#include "Engine/Math/Ray.h"

AICharacter::AICharacter(Character* opponent_, float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : Character(health_, meter_, isRunning_, isAirborne_, model_,  position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_) {
	opponent = opponent_;
	SetMaxSpeed(3.0f);
	targetShifted = false;
}

void AICharacter::Update(const float deltaTime_)
{
	target = opponent->GetPosition() + -maxSpeed * glm::rotate(glm::vec3(1.0f, 0.0f, 0.0f), opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
	
	Ray ray = Ray();
	ray.direction = vel;
	ray.origin = position;
	CollisionDetection::RayObbIntersection(&ray, &opponent->GetBoundingBox());
	if (ray.intersectionDist < maxSpeed/deltaTime_)
	{
		target += glm::cross(ray.direction, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	

	KinematicSteeringOutput steering = KinematicSeek::getSteering(this, target);
	vel = steering.velocity;
	angle = steering.rotation;
	Character::Update(deltaTime_);
}
