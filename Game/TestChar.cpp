#include "TestChar.h"
#include "Decision Tree/FloatDecision.h"

TestChar::~TestChar()
{
	decision = nullptr;
	delete decision;
}

TestChar::TestChar(float health_)
{
	health = health_;
	decision = new FloatDecision(1.0f, 5.0f);
	decision->SetChar(this);
	decision->SetTrueNode(new Action("greater"));
	decision->SetFalseNode(new Action("lesser"));
}

void TestChar::runDecisionTree()
{
	decision->MakeDecision();
}