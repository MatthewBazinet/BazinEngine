#include "ActionUnique.h"

ActionUnique::ActionUnique()
{
	word = "Unique";
}

DecisionTreeNode* ActionUnique::MakeDecision()
{
	ai->UseUnique();
	return this;
}
