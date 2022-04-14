#include "ActionEXTatsu.h"

ActionEXTatsu::ActionEXTatsu()
{
	word = "EXTatsu";
}

DecisionTreeNode* ActionEXTatsu::MakeDecision()
{
	ai->UseEXTatsu();
	return this;
}
