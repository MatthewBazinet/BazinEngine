#ifndef WANTTOHEAVY_H
#define WANTTOHEAVY_H


#include "Game/Decision Tree/Decision.h"
#include "AICharacter.h"
class WantToHeavy :
	public Decision
{
	AICharacter* ai;
	virtual DecisionTreeNode* GetBranch();
public:
	void SetAI(AICharacter* ai_);
};

#endif // !WANTTOHEAVY_H