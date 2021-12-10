#ifndef DECISION_H
#define DECISION_H

#include "DecisionTreeNode.h"


class Decision : public DecisionTreeNode
{
protected:
	DecisionTreeNode* trueNode;
	DecisionTreeNode* falseNode;
	bool decision;
	

public:
	Decision();
	virtual ~Decision() {};

	virtual DecisionTreeNode* MakeDecision() override;
	virtual DecisionTreeNode* GetBranch();
	void SetTrueNode(DecisionTreeNode* node_) { trueNode = node_; };
	void SetFalseNode(DecisionTreeNode* node_) { falseNode = node_; };

	
};

#endif;