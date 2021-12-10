#ifndef ACTION_H
#define ACTION_H

#include "DecisionTreeNode.h"
#include "../tinyxml2.h"
using namespace tinyxml2;
class Action : public DecisionTreeNode
{
private:
	std::string word;

public:
	Action(std::string word_);
	Action(XMLElement* element);
	virtual ~Action() {};
	DecisionTreeNode* MakeDecision();
};

#endif;