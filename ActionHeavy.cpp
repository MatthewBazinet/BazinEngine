#include "ActionHeavy.h"

ActionHeavy::ActionHeavy()
{
	word = "Heavy";
}

DecisionTreeNode* ActionHeavy::MakeDecision()
{
	ai->UseHeavy();
	return this;
}
