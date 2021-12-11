#include "AICharacter.h"
#include <glm/gtx/rotate_vector.hpp>
#include "Engine/Math/CollisionDetection.h"
#include "Engine/Math/Ray.h"
#include "Game/Decision Tree/Decision.h"
#include "Game/Decision Tree/Action.h"
#include "wantToSpendMeter.h"
#include "WantToEXFireball.h"
#include "WantToMeteredCrossUp.h"
#include "WantToMeterlessCrossUp.h"
#include "WantToAttack.h"
#include "WantToBackAway.h"
#include "ActionEXFireball.h"
#include "ActionFireball.h"
#include "ActionMeteredCrossUp.h"
#include "ActionMeterlessCrossUp.h"
#include "ActionBackAway.h"
#include "ActionMoveTowards.h"
#include "ActionRunTowards.h"
#include <thread>

AICharacter::AICharacter(Character* opponent_, float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : Character(health_, meter_, isRunning_, isAirborne_, model_,  position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_) {
	opponent = opponent_;
	SetMaxSpeed(7.0f);
	targetShifted = false;
	projectile = nullptr;
	dir2D = 1.0f;
	decisionTree = CreateTree();

	wantToSpendMeter = 0.0f;
	wantToEXFireball = 0.0f;
	wantToMeteredCrossUp = 0.0f;

	wantToMeterlessCrossUp = 0.0f;
	wantToAttack = 0.0f;
	wantToBackAway = 0.0f;
	isExisting = true;
	decisionTreeThread = new std::thread(&AICharacter::RunDecisionTree, this);
}

AICharacter::~AICharacter()
{
	delete projectile;
	projectile = nullptr;
	delete decisionTree;
	decisionTree = nullptr;
	isExisting = false;
	decisionTreeThread->join();
	delete decisionTreeThread;

}

void AICharacter::Update(const float deltaTime_)
{
	overclock += deltaTime_ * 1;
	wantToSpendMeter += deltaTime_* RandBetween(0.1, 0.3);
	wantToEXFireball += deltaTime_ * RandBetween(0.1, 0.3);
	wantToMeteredCrossUp += deltaTime_ * RandBetween(0.1, 0.3);

	wantToMeterlessCrossUp += deltaTime_ * RandBetween(0.1, 0.3);
	wantToAttack += deltaTime_ * RandBetween(0.1, 0.3);
	wantToBackAway += deltaTime_ * RandBetween(0.1, 0.3);

	if (position.y >= 0.1f)
	{
		isAirborne = true;
	}
	if (position.y <= -0.1f)
	{
		position.y = 0.0f;
		vel.y = 0.0f;
		accel.y = 0.0f;
		isAirborne = false;
	}

	if (getIsAirborne())
	{
		ApplyForce(glm::vec3(accel.x, -9.81f * mass, accel.z));
	}

	//std::vector<glm::vec3> targets;
	//targets.push_back(glm::vec3(2.0f, 0.0f, 5.0f));
	//targets.push_back(glm::vec3(7.0f, 0.0f, 7.0f));
	
	switch (targetType) {
	case TargetType::CROSSUP:
		target = opponent->GetPosition() + -maxSpeed * glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case TargetType::INFRONTCLOSE:
		target = opponent->GetPosition() + maxSpeed * 0.75f * glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
		break;

	case TargetType::INFRONTFAR:
		target = opponent->GetPosition() + maxSpeed * glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
		break;

	case TargetType::SELF:
		target = position;
		break;
	default:
		target = position;
		break;
	}
	Ray ray = Ray();
	ray.direction = vel;
	ray.origin = position;
	BoundingBox tmp = opponent->GetBoundingBox();
	CollisionDetection::RayObbIntersection(&ray, &tmp);
	
	KinematicSteeringOutput steering;
	if (ray.intersectionDist < maxSpeed / deltaTime_)
	if (isRunning)
	{
		//target = opponent->GetPosition() + -maxSpeed * glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
		Ray ray = Ray();
		ray.direction = vel;
		ray.origin = position;
		BoundingBox tmp = opponent->GetBoundingBox();
		CollisionDetection::RayObbIntersection(&ray, &tmp);
		if (ray.intersectionDist < maxSpeed / deltaTime_)
		{
			target += glm::cross(ray.direction, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		steering = KinematicArrive::getSteering(this, target, 1.3f);
		float preserveY = vel.y;
		vel = steering.velocity;
		vel.y = preserveY;

		if (projectile != nullptr)
		{
			target = projectile->GetPosition();


			if (glm::distance(position, projectile->GetPosition()) < 3.0f)
			{
				steering = KinematicFlee::getSteering(this, projectile->GetPosition());
				float preserveY = vel.y;
				vel = steering.velocity;
				vel.y = preserveY;

			}

			if (glm::distance(position, projectile->GetPosition()) < 5.0f)
			{
				if (getIsAirborne() == false)
				{
					SetVelocity(glm::vec3(GetVelocity().x, 10.0f, GetVelocity().z));
				}
			}

		}
		angle = steering.rotation;
	}
	else
	{
		//target = opponent->GetPosition() + -maxSpeed * glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
		//steering = KinematicChainArrive::getSteering(this, targets, 1.0f);
		//float preserveY = vel.y;
		//vel = steering.velocity;
		//vel.y = preserveY;

		glm::vec3 projection = glm::dot(position - target, axisOf2DMovement) * axisOf2DMovement;
		glm::vec3 axisMagProj = glm::length(projection) * axisOf2DMovement;

		if (glm::equal(axisMagProj - projection, glm::vec3(0.0f,0.0f,0.0f)).b) {
			SetDir2D(-1.0f);
		}
		else
		{
			SetDir2D(1.0f);
		}
		
		projection = glm::dot(target, axisOf2DMovement) * axisOf2DMovement;

		if (glm::distance(projection, position) < 1.0f) {
			SetDir2D(0.0f);
		}
		if (targetType == TargetType::SELF)
		{
			SetDir2D(0.0f);
		}

		if (!opponent->getIsRunning() && getIsAirborne() == false)
		{
			axisOf2DMovement = glm::normalize(opponent->GetPosition() - position);
		}
		float preserveY = vel.y;
		vel = axisOf2DMovement * maxSpeed * dir2D;
		vel.y = preserveY;
		if (projectile) {
			if (glm::distance(position, projectile->GetPosition()) < 5.0f)
			{
				if (getIsAirborne() == false)
				{
					SetVelocity(glm::vec3(GetVelocity().x, 10.0f, GetVelocity().z));
					isAirborne = true;
				}
			}
		}

		if (glm::distance(position, opponent->GetPosition()) < 2.0f && targetType != TargetType::SELF)
		{
			if (getIsAirborne() == false)
			{
				SetVelocity(glm::vec3(GetVelocity().x, 10.0f, GetVelocity().z));
				isAirborne = true;
			}
		}
	angle = steering.rotation;

	}
	if (position.y >= 0.1f)
	{
		isAirborne = true;
	}

	if (position.y <= -0.1f)
	{
		position.y = 0.0f;
		vel.y = 0.0f;
		accel.y = 0.0f;
		isAirborne = false;
	}

	if (getIsAirborne())
	{
		ApplyForce(glm::vec3(accel.x, -9.81f * mass, accel.z));
	}

	GameObject::Update(deltaTime_);

	if (!isRunning) {
		if (!opponent->getIsRunning() && getIsAirborne() == false)
		{
			axisOf2DMovement = camera->GetRight();
		}

		dir2D = 0.0f;
		if (MovingLeft) dir2D = -1.0f;
		if (MovingRight) dir2D = 1.0f;


		float preserveY = vel.y;
		vel = axisOf2DMovement * maxSpeed * dir2D;
		vel.y = preserveY;
	}


	if (vel != glm::vec3())	angle = atan2(vel.x, vel.z);;

	proj->Update(deltaTime_);
}

void AICharacter::SetDir2D(float dir_)
{
	if (abs(dir_) > 0.0f || abs(dir_) < 1.0f)
	{
		if (dir_ == 0.0f)
		{
			dir2D = 0.0f;
		}
		else
		{
			dir2D = (dir_ > 0.0f) ? 1.0f : -1.0f;
		}
	}
	else
	{
		dir2D = dir_;
	}
}

void AICharacter::UseEXFireball()
{
	QCF(3, true);
	wantToEXFireball = 0.0f;
	wantToSpendMeter = 0.0f;
	printf("EX Fireball used\n");

}

void AICharacter::UseFireball()
{
	QCF(1, true);
	wantToAttack = 0.0f;
	printf("Fireball used\n");
}

void AICharacter::MeteredCrossUp()
{
	Run(true);
	targetType = TargetType::CROSSUP;
	wantToMeteredCrossUp = 0.0f;
	wantToSpendMeter = 0.0f;
	printf("Metered Crossup\n");
}

void AICharacter::MeterlessCrossUp()
{
	Run(false);
	targetType = TargetType::CROSSUP;
	wantToMeterlessCrossUp = 0.0f;
	printf("Meterless Crossup\n");
}

void AICharacter::BackAway()
{
	Run(false);
	targetType = TargetType::INFRONTFAR;
	printf("Back Away\n");
}

void AICharacter::MoveTowards()
{
	Run(false);
	targetType = TargetType::INFRONTCLOSE;
	printf("Move Towards\n");
}

void AICharacter::RunTowards()
{
	Run(true);
	targetType = TargetType::INFRONTCLOSE;
	wantToSpendMeter = 0.0f;
	printf("Run Towards\n");
}


DecisionTreeNode* AICharacter::CreateTree()
{
	WantToSpendMeter* wantToSpendMeter = new WantToSpendMeter();
	wantToSpendMeter->SetAI(this);
	WantToEXFireball* wantToEXFireball = new WantToEXFireball();
	wantToEXFireball->SetAI(this);
	ActionEXFireball* EXFireball = new ActionEXFireball();
	EXFireball->SetAI(this);
	wantToSpendMeter->SetTrueNode(wantToEXFireball);
	wantToEXFireball->SetTrueNode(EXFireball);
	WantToMeteredCrossUp* wantToMeteredCrossUp = new WantToMeteredCrossUp();
	wantToMeteredCrossUp->SetAI(this);
	ActionMeteredCrossUp* runningCrossUp = new ActionMeteredCrossUp();
	runningCrossUp->SetAI(this);
	wantToMeteredCrossUp->SetTrueNode(runningCrossUp);
	ActionRunTowards* runTowards = new ActionRunTowards();
	runTowards->SetAI(this);
	wantToMeteredCrossUp->SetFalseNode(runTowards);
	wantToEXFireball->SetFalseNode(wantToMeteredCrossUp);

	WantToMeterlessCrossUp* wantToMeterlessCrossUp = new WantToMeterlessCrossUp();
	wantToMeterlessCrossUp->SetAI(this);
	wantToSpendMeter->SetFalseNode(wantToMeterlessCrossUp);
	ActionMeterlessCrossUp* meterlessCrossUp = new ActionMeterlessCrossUp();
	meterlessCrossUp->SetAI(this);
	wantToMeterlessCrossUp->SetTrueNode(meterlessCrossUp);
	WantToAttack* wantToAttack = new WantToAttack();
	wantToAttack->SetAI(this);
	wantToMeterlessCrossUp->SetFalseNode(wantToAttack);
	ActionFireball* fireball = new ActionFireball();
	fireball->SetAI(this);
	wantToAttack->SetTrueNode(fireball);
	WantToBackAway* wantToBackAway = new WantToBackAway();
	wantToBackAway->SetAI(this);
	wantToAttack->SetFalseNode(wantToBackAway);
	ActionBackAway* backAway = new ActionBackAway();
	backAway->SetAI(this);
	wantToBackAway->SetTrueNode(backAway);
	ActionMoveTowards* moveTowards = new ActionMoveTowards();
	moveTowards->SetAI(this);
	wantToBackAway->SetFalseNode(moveTowards);

	return wantToSpendMeter;
}

void AICharacter::RunDecisionTree()
{
	while (isExisting)
	{
		if (this && decisionTree != nullptr) 
		{
			decisionTree->MakeDecision();
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
	}
}
