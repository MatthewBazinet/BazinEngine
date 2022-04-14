#include "ActionTatsu.h"

ActionTatsu::ActionTatsu()
{
	word = "Tatsu";
}

DecisionTreeNode* ActionTatsu::MakeDecision()
{
	ai->UseTatsu();
	return this;
}
