#include "Decision.h"

Decision::Decision()
{
	
	decision = true;
}

DecisionTreeNode* Decision::MakeDecision()
{
	DecisionTreeNode* branch = GetBranch();
	return branch->MakeDecision();
}

DecisionTreeNode* Decision::GetBranch()
{

	if (decision)
	{
		return trueNode;
	}
	return falseNode;
}