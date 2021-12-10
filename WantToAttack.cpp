#include "WantToAttack.h"

DecisionTreeNode* WantToAttack::GetBranch()
{
	if (ai->GetWantToAttack() > 1.0f)
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

void WantToAttack::SetAI(AICharacter* ai_)
{
	ai = ai_;
}