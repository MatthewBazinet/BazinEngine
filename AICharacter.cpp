#include "AICharacter.h"
#include <glm/gtx/rotate_vector.hpp>
#include "Engine/Math/CollisionDetection.h"
#include "Engine/Math/Ray.h"
#include "Game/Decision Tree/Decision.h"
#include "Game/Decision Tree/Action.h"
#include "wantToSpendMeter.h"
#include "WantToEXFireball.h"
#include "WantToEXTatsu.h"
#include "WantToFireball.h"
#include "WantToTatsu.h"
#include "WantToLight.h"
#include "WantToMedium.h"
#include "WantToHeavy.h"
#include "WantToUnique.h"
#include "WantToMeteredCrossUp.h"
#include "WantToMeterlessCrossUp.h"
#include "WantToAttack.h"
#include "WantToBackAway.h"
#include "ActionEXFireball.h"
#include "ActionEXTatsu.h"
#include "ActionFireball.h"
#include "ActionTatsu.h"
#include "ActionLight.h"
#include "ActionMedium.h"
#include "ActionHeavy.h"
#include "ActionUnique.h"
#include "ActionMeteredCrossUp.h"
#include "ActionMeterlessCrossUp.h"
#include "ActionBackAway.h"
#include "ActionMoveTowards.h"
#include "ActionRunTowards.h"

AICharacter::AICharacter(Character* character_){
	character = character_;
	targetShifted = false;
	projectile = nullptr;
	//DecisionTreeNode treeReaderTest = XMLDecisionTreeReader::ReadFile("Resources/Trees/Tree.xml");
	decisionTree = CreateTree();

	wantToSpendMeter = 0.0f;
	wantToEXFireball = 0.0f;
	wantToMeteredCrossUp = 0.0f;

	wantToMeterlessCrossUp = 0.0f;
	wantToAttack = 0.0f;
	wantToBackAway = 0.0f;
	isExisting = true;
	timeSinceLastDecision = 0.0f;
}

AICharacter::~AICharacter()
{
	delete projectile;
	projectile = nullptr;
	delete decisionTree;
	decisionTree = nullptr;
	character = nullptr;
	isExisting = false;

}

void AICharacter::Update(const float deltaTime_)
{
	wantToSpendMeter += deltaTime_* RandBetween(0.1, 0.3);
	wantToEXFireball += deltaTime_ * RandBetween(0.1, 0.3);
	wantToMeteredCrossUp += deltaTime_ * RandBetween(0.1, 0.3);

	wantToMeterlessCrossUp += deltaTime_ * RandBetween(0.1, 0.3);
	wantToAttack += deltaTime_ * RandBetween(0.1, 0.3);
	wantToBackAway += deltaTime_ * RandBetween(0.1, 0.3);
	timeSinceLastDecision += deltaTime_;

	if (timeSinceLastDecision > 2.0f)
	{
		RunDecisionTree();
		timeSinceLastDecision = 0.0f;
	}
	
	switch (targetType) {
	case TargetType::CROSSUP:
		target = character->opponent->GetPosition() + -character->maxSpeed * glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), character->opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case TargetType::INFRONTCLOSE:
		target = character->opponent->GetPosition() + character->maxSpeed * 0.75f * glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), character->opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
		break;

	case TargetType::INFRONTFAR:
		target = character->opponent->GetPosition() + character->maxSpeed * glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), character->opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
		break;

	case TargetType::SELF:
		target = character->position;
		break;
	default:
		target = character->position;
		break;
	}

	
	KinematicSteeringOutput steering;

	if (character->isRunning)
	{
		//target = opponent->GetPosition() + -maxSpeed * glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
		Ray ray = Ray();
		ray.direction = character->vel;
		ray.origin = character->position;
		BoundingBox tmp = character->opponent->GetBoundingBox();
		CollisionDetection::RayObbIntersection(&ray, &tmp);
		if (ray.intersectionDist < character->maxSpeed / deltaTime_)
		{
			target += glm::cross(ray.direction, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		steering = KinematicArrive::getSteering(character, target, 1.3f);
		float preserveY = character->vel.y;
		character->vel = steering.velocity;
		character->vel.y = preserveY;

		if (projectile != nullptr)
		{
			target = projectile->GetPosition();


			if (glm::distance(character->position, projectile->GetPosition()) < 3.0f)
			{
				steering = KinematicFlee::getSteering(character, projectile->GetPosition());
				float preserveY = character->vel.y;
				character->vel = steering.velocity;
				character->vel.y = preserveY;

			}

			if (glm::distance(character->position, projectile->GetPosition()) < 5.0f)
			{
				if (character->getIsAirborne() == false)
				{
					character->SetVelocity(glm::vec3(character->GetVelocity().x, 10.0f, character->GetVelocity().z));
				}
			}

		}
		character->angle = steering.rotation;
	}
	else
	{
		//target = opponent->GetPosition() + -maxSpeed * glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), opponent->GetAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
		//steering = KinematicChainArrive::getSteering(this, targets, 1.0f);
		//float preserveY = vel.y;
		//vel = steering.velocity;
		//vel.y = preserveY;

		glm::vec3 projection = glm::dot(character->position - target, character->axisOf2DMovement) * character->axisOf2DMovement;
		glm::vec3 axisMagProj = glm::length(projection) * character->axisOf2DMovement;

		if (glm::equal(axisMagProj - projection, glm::vec3(0.0f,0.0f,0.0f)).b) {
			character->Move(glm::vec2(-1, 0));
		}
		else
		{
			character->Move(glm::vec2(1, 0));
		}
		
		projection = glm::dot(target, character->axisOf2DMovement) * character->axisOf2DMovement;

		if (glm::distance(projection, character->position) < 1.0f) {
			character->Move(glm::vec2(0, 0));
		}
		if (targetType == TargetType::SELF)
		{
			character->Move(glm::vec2(0, 0));
		}

		if (projectile) {
			if (glm::distance(character->position, projectile->GetPosition()) < 5.0f)
			{
				if (character->getIsAirborne() == false)
				{
					character->Move(glm::vec2(0, 1));
					character->isAirborne = true;
				}
			}
		}

		if (glm::distance(character->position, opponent->GetPosition()) < 2.0f && targetType != TargetType::SELF)
		{
			character->Move(glm::vec2(0, 1));
		}

	}
}

void AICharacter::SetDir2D(float dir_)
{
	if (abs(dir_) > 0.0f || abs(dir_) < 1.0f)
	{
		if (dir_ == 0.0f)
		{
			character->dir2D = 0.0f;
		}
		else
		{
			character->dir2D = (dir_ > 0.0f) ? 1.0f : -1.0f;
		}
	}
	else
	{
		character->dir2D = dir_;
	}
}

void AICharacter::UseLight()
{
	character->Light();
}

void AICharacter::UseMedium()
{
	character->Medium();
}

void AICharacter::UseHeavy()
{
	character->Heavy();
}

void AICharacter::UseUnique()
{
	character->Unique();
}

void AICharacter::UseEXFireball()
{
	character->QCF(3, true);
	wantToEXFireball = 0.0f;
	wantToSpendMeter = 0.0f;
	printf("EX Fireball used\n");

}

void AICharacter::UseFireball()
{
	character->QCF(1, true);
	wantToAttack = 0.0f;
	printf("Fireball used\n");
}

void AICharacter::UseEXTatsu()
{
	character->QCB(2, false);
}

void AICharacter::UseTatsu()
{
	character->QCB(0, false);
}

void AICharacter::MeteredCrossUp()
{
	character->Run(true);
	targetType = TargetType::CROSSUP;
	wantToMeteredCrossUp = 0.0f;
	wantToSpendMeter = 0.0f;
	printf("Metered Crossup\n");
}

void AICharacter::MeterlessCrossUp()
{
	character->Run(false);
	targetType = TargetType::CROSSUP;
	wantToMeterlessCrossUp = 0.0f;
	printf("Meterless Crossup\n");
}

void AICharacter::BackAway()
{
	character->Run(false);
	targetType = TargetType::INFRONTFAR;
	printf("Back Away\n");
}

void AICharacter::MoveTowards()
{
	character->Run(false);
	targetType = TargetType::INFRONTCLOSE;
	printf("Move Towards\n");
}

void AICharacter::RunTowards()
{
	character->Run(true);
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
	WantToEXTatsu* wantToEXTatsu = new WantToEXTatsu();
	wantToEXTatsu->SetAI(this);
	ActionEXTatsu* EXTatsu = new ActionEXTatsu();
	EXTatsu->SetAI(this);
	wantToEXFireball->SetTrueNode(wantToEXTatsu);
	wantToEXTatsu->SetTrueNode(EXTatsu);
	WantToMeteredCrossUp* wantToMeteredCrossUp = new WantToMeteredCrossUp();
	wantToMeteredCrossUp->SetAI(this);
	ActionMeteredCrossUp* runningCrossUp = new ActionMeteredCrossUp();
	runningCrossUp->SetAI(this);
	wantToMeteredCrossUp->SetTrueNode(runningCrossUp);
	ActionRunTowards* runTowards = new ActionRunTowards();
	runTowards->SetAI(this);
	wantToMeteredCrossUp->SetFalseNode(runTowards);
	wantToEXTatsu->SetFalseNode(wantToMeteredCrossUp);

	WantToMeterlessCrossUp* wantToMeterlessCrossUp = new WantToMeterlessCrossUp();
	wantToMeterlessCrossUp->SetAI(this);
	wantToSpendMeter->SetFalseNode(wantToMeterlessCrossUp);
	ActionMeterlessCrossUp* meterlessCrossUp = new ActionMeterlessCrossUp();
	meterlessCrossUp->SetAI(this);
	wantToMeterlessCrossUp->SetTrueNode(meterlessCrossUp);
	WantToAttack* wantToAttack = new WantToAttack();
	wantToAttack->SetAI(this);
	wantToMeterlessCrossUp->SetFalseNode(wantToAttack);
	WantToFireball* wantToFireball = new WantToFireball();
	ActionFireball* fireball = new ActionFireball();
	fireball->SetAI(this);
	wantToAttack->SetTrueNode(fireball);
	WantToTatsu* wantToTatsu = new WantToTatsu();
	ActionTatsu* tatsu = new ActionTatsu();
	tatsu->SetAI(this);
	wantToFireball->SetFalseNode(wantToTatsu);
	wantToTatsu->SetTrueNode(tatsu);
	WantToLight* wantToLight = new WantToLight();
	ActionLight* light = new ActionLight();
	light->SetAI(this);
	wantToTatsu->SetFalseNode(wantToLight);
	wantToLight->SetTrueNode(light);

	WantToMedium* wantToMedium = new WantToMedium();
	ActionMedium* medium = new ActionMedium();
	light->SetAI(this);
	wantToLight->SetFalseNode(wantToMedium);
	wantToMedium->SetTrueNode(medium);

	WantToHeavy* wantToHeavy = new WantToHeavy();
	ActionHeavy* heavy = new ActionHeavy();
	light->SetAI(this);
	wantToMedium->SetFalseNode(wantToHeavy);
	wantToHeavy->SetTrueNode(heavy);

	ActionUnique* unique = new ActionUnique();
	unique->SetAI(this);
	wantToHeavy->SetFalseNode(unique);

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
		}
	}
}
