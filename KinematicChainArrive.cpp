#include "KinematicChainArrive.h"

KinematicSteeringOutput KinematicChainArrive::getSteering(GameObject* character_, std::vector<glm::vec3> targets_, float timeToTarget_)
{
	KinematicSteeringOutput result = KinematicSteeringOutput();

    //std::cout << round(character_->GetPosition().x) << " " << targets_[counter].x << std::endl;
    if (abs(character_->GetPosition().x - targets_[character_->GetTargetNumber()].x) < 0.2f 
		&& abs(character_->GetPosition().z -targets_[character_->GetTargetNumber()].z) < 0.2f 
		&& character_->GetTargetNumber() < targets_.size() - 1)
    {
        //std::cout << "moving to " << targets_[character_->GetTargetNumber()].x << " " << targets_[character_->GetTargetNumber()].z << std::endl;
        character_->SetTargetNumber(character_->GetTargetNumber() + 1);
    }
    if (character_->GetPosition() != targets_[character_->GetTargetNumber()])
    {
        result.velocity = targets_[character_->GetTargetNumber()] - character_->GetPosition();
        //result.velocity.y = 0.0f;
        // velocity is along this direction, at full speed
        result.velocity /= timeToTarget_;
        if (result.velocity.length() != character_->GetMaxSpeed())
        {
            result.velocity = glm::normalize(result.velocity);
            result.velocity = character_->GetMaxSpeed() * result.velocity;
        }

        // face in direction we want to move
        result.rotation = LookAt(result.velocity);
        return result;
    }
}

float KinematicChainArrive::LookAt(glm::vec3 velocity)
{
	return atan2(velocity.x, velocity.z);
}
