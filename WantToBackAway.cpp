#include "WantToBackAway.h"

DecisionTreeNode* WantToBackAway::GetBranch()
{
	if (ai->GetWantToBackAway() > 1.0f)
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

void WantToBackAway::SetAI(AICharacter* ai_)
{
	ai = ai_;
}