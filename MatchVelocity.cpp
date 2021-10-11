#include "MatchVelocity.h"

SteeringOutput MatchVelocity::getSteering(GameObject* character_, GameObject* target_, float timeToTarget_, glm::vec3 maxAccel_)
{
    SteeringOutput result = SteeringOutput();

    glm::vec3 tmp1 = character_->GetVelocity();
    glm::vec3 tmp2 = target_->GetVelocity();

    result.linear = tmp2 - tmp1;
    std::cout << tmp2.y << std::endl;
    result.linear /= timeToTarget_;
    if (result.linear.x > maxAccel_.x || result.linear.x < maxAccel_.x * -1) {
        result.linear.x = glm::normalize(result.linear.x);
        result.linear.x *= maxAccel_.x;
    }
    if (result.linear.y > maxAccel_.y || result.linear.y < maxAccel_.y * -1) {
        result.linear.y = glm::normalize(result.linear.y);
        result.linear.y *= maxAccel_.y;
    }
    if (result.linear.z > maxAccel_.z || result.linear.z < maxAccel_.z * -1) {
        result.linear.z = glm::normalize(result.linear.z);
        result.linear.z *= maxAccel_.z;
    }
    if (target_->GetVelocity().x ==0.0f) {
        result.linear.x = 0.0f;
    }
    if (target_->GetVelocity().y == 0.0f) {
        result.linear.y = 0.0f;
    }
    if (target_->GetVelocity().z == 0.0f) {
        result.linear.z = 0.0f;
    }
    //result.angular = 0;
    
    return result;
}
