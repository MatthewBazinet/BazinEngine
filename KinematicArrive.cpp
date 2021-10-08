#include "KinematicArrive.h"

KinematicSteeringOutput KinematicArrive::getSteering(GameObject* character_, glm::vec3 target_, float timeToTarget_)
{
    KinematicSteeringOutput result = KinematicSteeringOutput();

    // Get direction to the target, as a new vector
    result.velocity = target_ - character_->GetPosition();
    //result.velocity.y = 0.0f;
    // velocity is along this direction, at full speed
    result.velocity /= timeToTarget_;
    if (result.velocity.length() > character_->GetMaxSpeed())
    {
        result.velocity = glm::normalize(result.velocity);
        result.velocity = character_->GetMaxSpeed() * result.velocity;
    }

    // face in direction we want to move

    result.rotation = LookAt(result.velocity);
    return result;
}


float KinematicArrive::LookAt(glm::vec3 velocity)
{
    return  atan2(velocity.x, velocity.z);
}
