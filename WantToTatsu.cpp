#include "WantToTatsu.h"

DecisionTreeNode* WantToTatsu::GetBranch()
{
	if (ai->GetWantToTatsu())
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

void WantToTatsu::SetAI(AICharacter* ai_)
{
	ai = ai_;
}
