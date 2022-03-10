#ifndef AICHARACTER
#define AICHARACTER

#include "Game/Character.h"
#include "KinematicFlee.h"
#include "KinematicArrive.h"
#include "KinematicChainArrive.h"
#include "Game/Decision Tree/DecisionTreeNode.h"
#include <cstdlib>
#include <thread>

//#include "Game/Decision Tree/FloatDecision.h"

enum TargetType {CROSSUP, INFRONTCLOSE, INFRONTFAR, SELF};

//class FloatDecision;

class AICharacter :
	public Character
{

public:
	AICharacter(Character* opponent_, float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat orientation_ = glm::quat(0.0f, 5.0f, 5.0f, 5.0f), glm::quat angularVelocity_ = glm::quat());
	~AICharacter();
	void SetOpponent(Character* opponent_) { opponent = opponent_; };
	void SetProjectile(Projectile* projectile_) { projectile = projectile_; };

	void Update(const float deltaTime);
	void SetTargetType(TargetType targetType_) { targetType = targetType_; };
	glm::vec3 GetTarget() { return target; };
	void SetDir2D(float dir_);
	//FloatDecision* GetDecision() { return decisionTree; };
	//FloatDecision* decisionTree;
	float GetOverclock() {return overclock;};

	float GetWantToSpendMeter() { return wantToSpendMeter; };
	float GetWantToEXFireball() { return wantToEXFireball; };
	float GetWantToMeteredCrossUp() { return wantToMeteredCrossUp; };

	float GetWantToMeterlessCrossUp() { return wantToMeterlessCrossUp; };
	float GetWantToAttack() { return wantToAttack; };
	float GetWantToBackAway() { return wantToBackAway; };

	void UseEXFireball();
	void UseFireball();
	void MeteredCrossUp();
	void MeterlessCrossUp();
	void BackAway();
	void MoveTowards();
	void RunTowards();
	
private:
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
	float wantToMeteredCrossUp;

	float wantToMeterlessCrossUp;
	float wantToAttack;
	float wantToBackAway;
	bool isExisting;
	std::thread* decisionTreeThread;

	float RandBetween(float lo, float hi) {
		return lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
	};

};

#endif