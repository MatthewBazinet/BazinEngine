#include "MatchVelocity.h"

SteeringOutput MatchVelocity::getSteering(GameObject* character_, GameObject* target_, float timeToTarget_, glm::vec3 maxAccel_)
{
    SteeringOutput result = SteeringOutput();

    glm::vec3 tmp1 = character_->GetVelocity();
    glm::vec3 tmp2 = target_->GetVelocity();

    result.linear = tmp1 - tmp2;
   
    result.linear /= timeToTarget_;
    if (result.linear.x > maxAccel_.x || result.linear.x < maxAccel_.x * -1) {
        result.linear = glm::normalize(result.linear);
        result.linear = maxAccel_ * result.linear;
    }
    if (result.linear.y > maxAccel_.y || result.linear.y < maxAccel_.y * -1) {
        result.linear = glm::normalize(result.linear);
        result.linear = maxAccel_ * result.linear;
    }
    if (result.linear.z > maxAccel_.z || result.linear.z < maxAccel_.z * -1) {
        result.linear = glm::normalize(result.linear);
        result.linear = maxAccel_ * result.linear;
    }
    result.angular = 0;
   
    return result;
}
