#include "ActionEXFireball.h"

ActionEXFireball::ActionEXFireball()
{
	word = "EXFireball";
}

DecisionTreeNode* ActionEXFireball::MakeDecision()
{
	ai->UseEXFireball();
	return this;
}
