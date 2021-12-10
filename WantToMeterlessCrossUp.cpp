#include "WantToMeterlessCrossUp.h"

DecisionTreeNode* WantToMeterlessCrossUp::GetBranch()
{
	if (ai->GetWantToMeterlessCrossUp() > 1.0f)
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

void WantToMeterlessCrossUp::SetAI(AICharacter* ai_)
{
	ai = ai_;
}