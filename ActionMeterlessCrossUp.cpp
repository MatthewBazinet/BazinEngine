#include "ActionMeterlessCrossUp.h"

ActionMeterlessCrossUp::ActionMeterlessCrossUp()
{
	word = "MeterlessCrossUp";
}

DecisionTreeNode* ActionMeterlessCrossUp::MakeDecision()
{
	ai->MeterlessCrossUp();
	return this;
}
