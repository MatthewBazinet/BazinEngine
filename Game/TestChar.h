#ifndef TESTCHAR_H
#define TESTCHAR_H

#include "../Game/Decision Tree/Action.h"
class FloatDecision;
class TestChar
{
private:
	float health;
	FloatDecision* decision;
	DecisionTreeNode* greater;
	DecisionTreeNode* lesser;

public:
	TestChar();
	TestChar(float health_);
	~TestChar() {};
	float GetHealth() { return health; };
	void SetHealth(float health_) { health = health_; };

	void runDecisionTree();
};

#endif;