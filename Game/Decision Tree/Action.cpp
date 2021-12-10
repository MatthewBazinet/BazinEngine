#include "Action.h"

Action::Action()
{
	word = "";
}

Action::Action(std::string word_)
{
	word = word_;
}

DecisionTreeNode* Action::MakeDecision()
{
	std::cout << word << std::endl;
	return dynamic_cast<DecisionTreeNode*>(this);
}