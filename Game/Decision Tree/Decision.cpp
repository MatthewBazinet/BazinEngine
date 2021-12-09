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
	XMLDocument doc;
	//this parses the xml file allowing you to read the values inside of it.
	doc.LoadFile(" ");
	//this is the root node
	XMLElement* decisionNode = doc.FirstChildElement(" ");
	//this is the child of the root node
	XMLElement* branch = decisionNode->FirstChildElement(" ");

	if (decision)
	{
		return trueNode;
	}
	return falseNode;
}