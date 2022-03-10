#include "ActionMoveTowards.h"


ActionMoveTowards::ActionMoveTowards()
{
	word = "MoveTowards";
}

DecisionTreeNode* ActionMoveTowards::MakeDecision()
{
	ai->MoveTowards();
	return this;
}
