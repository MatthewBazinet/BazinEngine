#include "WantToFireball.h"

DecisionTreeNode* WantToFireball::GetBranch()
{
	if (ai->GetWantToFireball() > 1.0f)
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

void WantToFireball::SetAI(AICharacter* ai_)
{
	ai = ai_;
}