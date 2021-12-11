#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H

#include <stdio.h>
#include <string>
#include <iostream>

class DecisionTreeNode
{
private:
	DecisionTreeNode* whatToDo;

public:
	DecisionTreeNode();
	virtual ~DecisionTreeNode() { delete whatToDo; whatToDo = nullptr; };
	virtual DecisionTreeNode* MakeDecision();
};

#endif;