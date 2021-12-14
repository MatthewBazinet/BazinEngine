#include "XMLDecision.h"

XMLDecision::XMLDecision()
{
}

XMLDecision::~XMLDecision()
{
}

DecisionTreeNode* XMLDecision::MakeDecision()
{
    return nullptr;
}



void XMLDecision::SetDecision(std::vector<std::string> decision_)
{
    root = decision_.front();
}
