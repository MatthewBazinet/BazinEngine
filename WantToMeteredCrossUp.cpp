#include "WantToMeteredCrossUp.h"

DecisionTreeNode* WantToMeteredCrossUp::GetBranch()
{
	if (ai->GetWantToMeteredCrossUp() > 1.0f && ai->GetOverclock() > 15.0f)
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

void WantToMeteredCrossUp::SetAI(AICharacter* ai_)
{
	ai = ai_;
}