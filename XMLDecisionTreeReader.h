#ifndef XMLDECISIONTREEREADER_H

#include "Game/Decision Tree/DecisionTreeNode.h"
#include "Game/Decision Tree/Decision.h"
#include "Game/Decision Tree/Action.h"
#include "XMLDecision.h"
#include "../tinyxml2.h"
#include <vector>
#include <stack>
using namespace tinyxml2;
class XMLDecisionTreeReader
{
public:
	DecisionTreeNode ReadFile(const char* filepath_);
private:
	//std::vector<XMLDecision*> decision;
};

#endif