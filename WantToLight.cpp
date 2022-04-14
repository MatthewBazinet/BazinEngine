#include "WantToLight.h"

DecisionTreeNode* WantToLight::GetBranch()
{
	if (ai->GetWantToLight())
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

void WantToLight::SetAI(AICharacter* ai_)
{
	ai = ai_;
}
