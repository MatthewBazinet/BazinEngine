#include "WantToEXTatsu.h"

DecisionTreeNode* WantToEXTatsu::GetBranch()
{
	if (ai->GetWantToSpendMeter() > 1.0f && ai->GetCharacter()->GetOverclock() > 25.0f)
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

void WantToEXTatsu::SetAI(AICharacter* ai_)
{
	ai = ai_;
}
