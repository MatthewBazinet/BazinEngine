#include "XMLDecisionTreeReader.h"

DecisionTreeNode XMLDecisionTreeReader::ReadFile(const char* filepath_)
{
	XMLDocument doc;
	//this parses the xml file allowing you to read the values inside of it.
	doc.LoadFile(filepath_);
	//this is the root node
	XMLElement* decisionNode = doc.FirstChildElement(" ");
	//this is the child of the root node
	XMLElement* branch = decisionNode->FirstChildElement(" ");
	return DecisionTreeNode();
}
