#include "BattleCamera.h"
#include "..//..//Game/Character.h"
#include <glm/gtx/vector_angle.hpp>

BattleCamera::BattleCamera(float height_) : Camera()
{
	height = height_;
	player1 = nullptr;
	player2 = nullptr;
	farPlane = 100.0f;
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

		if (distance < 5.0f)
		{
			//distance = 5.0f;
			return;
		}
		
		glm::vec3 diff;
		if (player1->FacingLeft())
		{
			diff = player1->GetPosition() - midpoint;
		}
		else
		{
			diff = player2->GetPosition() - midpoint;
		}

		diff = glm::cross(glm::normalize(diff), glm::vec3(0.0f,1.0f,0.0f));

		glm::vec3 camDiff = midpoint - position;
		camDiff.y = 0.0f;

		SetForward(diff);

		position = midpoint - 2.0f * distance * forward;

		position.y = height;

	}
}

void BattleCamera::SetPlayers(Character* player1_, Character* player2_)
{
	player1 = player1_;
	player2 = player2_;
}

void BattleCamera::ProcessMouseMovement(glm::vec2 offset_)
{
}

void BattleCamera::ProcessMouseZoom(int y_)
{
}
