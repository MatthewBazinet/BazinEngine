#ifndef ACTION_H
#define ACTION_H

#include "DecisionTreeNode.h"

class Action : public DecisionTreeNode
{
private:
	std::string word;

public:
	Action(std::string word_);
	virtual ~Action() {};
	DecisionTreeNode* MakeDecision();
};

#endif;