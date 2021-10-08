#include "KinematicSeek.h"

KinematicSteeringOutput KinematicSeek::getSteering(GameObject* character_, glm::vec3 target_)
{
    KinematicSteeringOutput result = KinematicSteeringOutput();

    // Get direction to the target, as a new vector
    result.velocity = target_ - character_->GetPosition();
    //result.velocity.y = 0.0f;
    // velocity is along this direction, at full speed
    result.velocity = glm::normalize(result.velocity);
    result.velocity = character_->GetMaxSpeed() * result.velocity;
    
    // face in direction we want to move
   
    result.rotation = LookAt(result.velocity);
    return result;
}


float KinematicSeek::LookAt(glm::vec3 velocity)
{
    return  atan2(velocity.x, velocity.z);
}
