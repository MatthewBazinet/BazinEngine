#ifndef ACTION_H
#define ACTION_H

#include "DecisionTreeNode.h"
#include "../tinyxml2.h"
using namespace tinyxml2;
class Action : public DecisionTreeNode
{
protected:
	std::string word;

public:
	Action();
	Action(std::string word_);
	Action(XMLElement* element);
	virtual ~Action() {};
	virtual DecisionTreeNode* MakeDecision();
};

#endif;