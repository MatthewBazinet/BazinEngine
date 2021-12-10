#ifndef XMLDECISIONTREEREADER_H

#include "Game/Decision Tree/DecisionTreeNode.h"
#include "../tinyxml2.h"
using namespace tinyxml2;
class XMLDecisionTreeReader
{
	DecisionTreeNode ReadFile(const char* filepath_);
};

#endif