#include "TestChar.h"
#include "../Game/Decision Tree/FloatDecision.h"

TestChar::TestChar()
{
	health = 0.0f;
}

TestChar::TestChar(float health_)
{
	health = health_;
}

void TestChar::runDecisionTree()
{
	decision = new FloatDecision(1.0f, 5.0f);
	decision->SetChar(this);
	greater = new Action("greater");
	lesser = new Action("lesser");

	decision->SetTrueNode(greater);
	decision->SetFalseNode(lesser);

	decision->MakeDecision();
}