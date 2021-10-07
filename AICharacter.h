#ifndef AICHARACTER
#define AICHARACTER

#include "Game/Character.h"
#include "KinematicFlee.h"

class AICharacter :
	public Character
{
public:
	AICharacter(Character* opponent_, float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat orientation_ = glm::quat(0.0f, 5.0f, 5.0f, 5.0f), glm::quat angularVelocity_ = glm::quat());
	void SetOpponent(Character* opponent_) { opponent = opponent_; };
	void Update(const float deltaTime);

	glm::vec3 GetTarget() { return target; };
	void SetTarget(glm::vec3 target_) { target = target_; };

private:
	glm::vec3 target;
	Character* opponent;
	bool targetShifted;
};

#endif