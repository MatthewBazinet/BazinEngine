#include "BattleCamera.h"
#include "..//..//Game/Character.h"
#include <glm/gtx/vector_angle.hpp>

BattleCamera::BattleCamera(float height_) : Camera()
{
	height = height_;
	player1 = nullptr;
	player2 = nullptr;
}

BattleCamera::BattleCamera() : Camera()
{
	height = 5.0f;
	player1 = nullptr;
	player2 = nullptr;
}

BattleCamera::~BattleCamera()
{
	player1 = nullptr;
	player2 = nullptr;
}

void BattleCamera::Update(const float deltaTime_)
{
	if (!(player1->getIsRunning() || player2->getIsRunning()))
	{
		glm::vec3 midpoint = player1->GetPosition() + player2->GetPosition();
		midpoint *= 0.5f;

		float distance = glm::distance(player1->GetPosition(), player2->GetPosition());
		
		glm::vec3 diff = midpoint - player2->GetPosition();
		glm::vec3 camDiff = midpoint - position;

		SetRotation(yaw + glm::angle(camDiff, diff), 0.0f, 0.0f);

		position = midpoint - 2.0f * distance * forward;

		position.y = height;

	}

}

void BattleCamera::SetPlayers(Character* player1_, Character* player2_)
{
	player1 = player1_;
	player2 = player2_;
}
