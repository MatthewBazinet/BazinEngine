#include "Pawn.h"

Pawn::Pawn(Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : GameObject(model_, position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_)
{
	SetMaxSpeed(1000.0f);
}

Pawn::~Pawn()
{
}

void Pawn::SetTarget(glm::vec3 target_)
{
	if(!grid)
	{
		return;
	}
	GridVec start;
	start.x = position.x;
	start.y = position.z;
	GridVec goal;
	goal.x = target_.x;
	goal.y = target_.y;
	std::unordered_map<GridVec, GridVec> cameFrom = std::unordered_map<GridVec, GridVec>();

	std::unordered_map<GridVec, double> costSoFar = std::unordered_map<GridVec, double>();

	Pathfinding::aStarSearch(*grid, start, goal, cameFrom, costSoFar);
	std::vector<GridVec> gridVecTargets = Pathfinding::makePath(start, goal, cameFrom);

	targets.clear();

	for (auto v : gridVecTargets)
	{
		glm::vec3 vectorTarget;
		vectorTarget.x = v.x;
		vectorTarget.y = 0.0f;
		vectorTarget.z = v.y;
		targets.push_back(vectorTarget);
	}
}

void Pawn::Update(const float deltaTime_)
{
	KinematicSteeringOutput kin = KinematicChainArrive::getSteering(this, targets, 1.5f);
	SetVelocity(kin.velocity);
	SetAngle(kin.rotation);
	GameObject::Update(deltaTime_);
}
