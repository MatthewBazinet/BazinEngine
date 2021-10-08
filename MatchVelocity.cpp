#include "MatchVelocity.h"

SteeringOutput MatchVelocity::getSteering(GameObject* character_, GameObject* target_, float timeToTarget_, float maxAccel_)
{
    SteeringOutput result = SteeringOutput();
    result.linear = target_->GetVelocity() - character_->GetVelocity();
    result.linear /= timeToTarget_;

    if (result.linear.length() > maxAccel_) {
        result.linear = glm::normalize(result.linear);
        result.linear *= maxAccel_;
    }
    return SteeringOutput();
}
