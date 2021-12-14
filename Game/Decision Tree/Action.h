#ifndef ACTION_H
#define ACTION_H

#include "DecisionTreeNode.h"

class Action : public DecisionTreeNode
{
protected:
	std::string word;

public:
	Action();
	Action(std::string word_);
	virtual ~Action() {};
	virtual DecisionTreeNode* MakeDecision();
};

#endif;