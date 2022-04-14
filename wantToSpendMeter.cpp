#include "wantToSpendMeter.h"

DecisionTreeNode* WantToSpendMeter::GetBranch()
{
	if (ai->GetWantToSpendMeter() > 1.0f && ai->GetCharacter()->GetOverclock() > 5.0f)
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

void WantToSpendMeter::SetAI(AICharacter* ai_)
{
	ai = ai_;
}
