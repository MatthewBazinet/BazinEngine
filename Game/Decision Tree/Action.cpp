#include "Action.h"

Action::Action(std::string word_)
{
	word = word_;
}

Action::Action(XMLElement* element)
{
}

DecisionTreeNode* Action::MakeDecision()
{
	std::cout << word << std::endl;
	return dynamic_cast<DecisionTreeNode*>(this);
}