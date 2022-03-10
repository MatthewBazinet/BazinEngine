#include "DecisionTreeNode.h"

DecisionTreeNode::DecisionTreeNode()
{

}

DecisionTreeNode* DecisionTreeNode::MakeDecision()
{
	if(whatToDo != nullptr)
	return whatToDo->MakeDecision();

	return nullptr;
}