#ifndef XMLDECISION_H
#define XMLDECISION_H
#include "Game/Decision Tree/Decision.h"
#include "../tinyxml2.h"
#include <vector>


class XMLDecision : public Decision
{
public:
	XMLDecision();
	~XMLDecision();

	DecisionTreeNode* MakeDecision();

	void SetDecision(std::vector<std::string> decision_);
	void SetTrueNode(DecisionTreeNode* node_) { trueNode = node_; };
	void SetFalseNode(DecisionTreeNode* node_) { falseNode = node_; };

	std::string GetString()const { return decision; }
	std::string GetRoot()const { return root; }
private:
	std::string root;
	std::string decision;
	DecisionTreeNode* trueNode;
	DecisionTreeNode* falseNode;
};
#endif

