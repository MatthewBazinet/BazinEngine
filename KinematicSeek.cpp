#include "KinematicSeek.h"

KinematicSteeringOutput KinematicSeek::getSteering(GameObject* character_, glm::vec3 target_)
{
    KinematicSteeringOutput result = KinematicSteeringOutput();

    result.velocity = target_ - character_->GetPosition();
    result.velocity = glm::normalize(result.velocity);
    result.velocity = character_->GetMaxSpeed() * result.velocity;

    result.rotation = LookAt(result.velocity);
    return result;
}

KinematicSteeringOutput KinematicSeek::PersueTarget(GameObject* character_, GameObject* target_)
{
    float maxPrediction = 100.0f;
    float prediction;
    glm::vec3 direction = target_->GetPosition() - character_->GetPosition();
    float distance = glm::distance(target_->GetPosition(), character_->GetPosition());
    float speed = std::sqrt(character_->GetVelocity().x * character_->GetVelocity().x + character_->GetVelocity().y * character_->GetVelocity().y + character_->GetVelocity().z * character_->GetVelocity().z);
   
   if (speed <= (distance / maxPrediction)) {
       prediction = maxPrediction;
   }
   else {
       prediction = distance / speed;
   }
   target_->GetPosition() += target_->GetVelocity() * prediction;
  // std::cout << prediction << std::endl;
    return getSteering(character_, target_->GetPosition());
}


float KinematicSeek::LookAt(glm::vec3 velocity)
{
    return  atan2(velocity.x, velocity.z);
}
