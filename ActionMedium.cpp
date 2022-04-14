#include "ActionMedium.h"

ActionMedium::ActionMedium()
{
	word = "Medium";
}

DecisionTreeNode* ActionMedium::MakeDecision()
{
	ai->UseMedium();
	return this;
}
