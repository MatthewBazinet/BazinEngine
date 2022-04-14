#include "WantToHeavy.h"

DecisionTreeNode* WantToHeavy::GetBranch()
{
	if (ai->GetWantToHeavy())
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

void WantToHeavy::SetAI(AICharacter* ai_)
{
	ai = ai_;
}
