#include "FloatDecision.h"
#include "Action.h"
#include "../TestChar.h"
#include "../Engine/Core/CoreEngine.h"

FloatDecision::FloatDecision(float minValue_, float maxValue_)
{
	minValue = minValue_;
	maxValue = maxValue_;
	trueNode = new Action("greater");
	falseNode = new Action("lesser");
}

DecisionTreeNode* FloatDecision::MakeDecision()
{
	DecisionTreeNode* branch = TestValue();
	return branch->MakeDecision();
}

DecisionTreeNode* FloatDecision::TestValue()
{
	std::cout << minValue << " " << testChar->GetHealth() << " " << maxValue << std::endl;
	if (minValue <= testChar->GetHealth() <= maxValue)
	{
		return trueNode;
	}
	return falseNode;
}

