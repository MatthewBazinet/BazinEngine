#include "ActionRunTowards.h"


ActionRunTowards::ActionRunTowards()
{
	word = "RunTowards";
}

DecisionTreeNode* ActionRunTowards::MakeDecision()
{
	ai->RunTowards();
	return this;
}
