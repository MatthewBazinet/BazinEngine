#include "WantToEXFireball.h"

DecisionTreeNode* WantToEXFireball::GetBranch()
{
	if (ai->GetWantToEXFireball() > 1.0f && ai->GetOverclock() > 50.0f)
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

void WantToEXFireball::SetAI(AICharacter* ai_)
{
	ai = ai_;
}