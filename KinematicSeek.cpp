#include "KinematicSeek.h"

KinematicSeek::KinematicSeek(Projectile* character_, glm::vec3 target_)
{
	character = character_;
	target = target_;
}

KinematicSeek::~KinematicSeek()
{
	if (result) { delete result; }
}

KinematicSteeringOutput KinematicSeek::getSteering()
{
    result = new KinematicSteeringOutput();

    // Get direction to the target, as a new vector
    result->velocity = target - character->GetPosition();
    
    // velocity is along this direction, at full speed
    result->velocity = glm::normalize(result->velocity);
    result->velocity = character->GetMaxSpeed() * result->velocity;

    // face in direction we want to move
    character->LookAt(result->velocity);

    result->rotation = 0;
    return *result;
}
