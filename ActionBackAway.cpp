#include "ActionBackAway.h"

ActionBackAway::ActionBackAway()
{
	word = "BackAway";
}

DecisionTreeNode* ActionBackAway::MakeDecision()
{
	ai->BackAway();
	return this;
}
