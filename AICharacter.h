#ifndef AICHARACTER
#define AICHARACTER

#include "Game/Character.h"
#include "KinematicFlee.h"
#include "KinematicArrive.h"
#include "KinematicChainArrive.h"
#include "Game/Decision Tree/DecisionTreeNode.h"
#include <cstdlib>

//#include "Game/Decision Tree/FloatDecision.h"

enum TargetType {CROSSUP, INFRONTCLOSE, INFRONTFAR, SELF};

//class FloatDecision;

class AICharacter
{

public:
	AICharacter(Character* character_);
	~AICharacter();
	void SetProjectile(Projectile* projectile_) { projectile = projectile_; };

	void Update(const float deltaTime);
	void SetTargetType(TargetType targetType_) { targetType = targetType_; };
	glm::vec3 GetTarget() { return target; };
	void SetDir2D(float dir_);

	float GetWantToSpendMeter() { return wantToSpendMeter; };
	float GetWantToEXFireball() { return wantToEXFireball; };
	float GetWantToEXTatsu() { return wantToEXTatsu; };
	float GetWantToMeteredCrossUp() { return wantToMeteredCrossUp; };

	float GetWantToMeterlessCrossUp() { return wantToMeterlessCrossUp; };
	float GetWantToAttack() { return wantToAttack; };
	float GetWantToFireball() { return wantToFireball; };
	float GetWantToTatsu() { return wantToTatsu; };
	float GetWantToLight() { return wantToLight; };
	float GetWantToMedium() { return wantToMedium; };
	float GetWantToHeavy() { return wantToHeavy; };
	float GetWantToUnique() { return wantToUnique; };

	float GetWantToBackAway() { return wantToBackAway; };

	void UseLight();
	void UseMedium();
	void UseHeavy();
	void UseUnique();
	void UseEXFireball();
	void UseFireball();
	void UseEXTatsu();
	void UseTatsu();
	void MeteredCrossUp();
	void MeterlessCrossUp();
	void BackAway();
	void MoveTowards();
	void RunTowards();

	Character* GetCharacter() { return character; };
	
private:
	Character* character;

	void SetTarget(glm::vec3 target_) { target = target_; };
	DecisionTreeNode* CreateTree();

	DecisionTreeNode* decisionTree;

	glm::vec3 target;
	Projectile* projectile;
	bool targetShifted;
	TargetType targetType;

	void RunDecisionTree();

	float wantToSpendMeter;
	float wantToEXFireball;
	float wantToEXTatsu;
	float wantToMeteredCrossUp;

	float wantToMeterlessCrossUp;
	float wantToAttack;
	float wantToLight;
	float wantToMedium;
	float wantToHeavy;
	float wantToUnique;
	float wantToTatsu;
	float wantToFireball;
	float wantToBackAway;

	bool isExisting;
	float timeSinceLastDecision;

};

static float RandBetween(float lo, float hi) {
	return lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
};

#endif