#include "KinematicFlee.h"

KinematicSteeringOutput KinematicFlee::getSteering(GameObject* character_, glm::vec3 target_)
{
    KinematicSteeringOutput result = KinematicSteeringOutput();

    // Get direction to the target, as a new vector
    result.velocity = character_->GetPosition() - target_;
    result.velocity.y = 0.0f;
    // velocity is along this direction, at full speed
    result.velocity = glm::normalize(result.velocity);
    result.velocity = character_->GetMaxSpeed() * result.velocity;

    // face in direction we want to move

    result.rotation = LookAt(result.velocity);
    return result;
}


float KinematicFlee::LookAt(glm::vec3 velocity)
{
    return  atan2(velocity.x, velocity.z);
}