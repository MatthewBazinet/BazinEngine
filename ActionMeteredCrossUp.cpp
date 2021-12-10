#include "ActionMeteredCrossUp.h"

ActionMeteredCrossUp::ActionMeteredCrossUp()
{
	word = "MeteredCrossUp";
}

DecisionTreeNode* ActionMeteredCrossUp::MakeDecision()
{
	ai->MeteredCrossUp();
	return this;
}
