#include "WantToUnique.h"

DecisionTreeNode* WantToUnique::GetBranch()
{
	if (ai->GetWantToUnique())
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

void WantToUnique::SetAI(AICharacter* ai_)
{
	ai = ai_;
}
