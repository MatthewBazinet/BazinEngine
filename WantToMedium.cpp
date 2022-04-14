#include "WantToMedium.h"

DecisionTreeNode* WantToMedium::GetBranch()
{
	if (ai->GetWantToMedium())
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

void WantToMedium::SetAI(AICharacter* ai_)
{
	ai = ai_;
}
