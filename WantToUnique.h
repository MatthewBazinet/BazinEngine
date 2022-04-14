#ifndef WANTTOUNIQUE_H
#define WANTTOUNIQUE_H


#include "Game/Decision Tree/Decision.h"
#include "AICharacter.h"
class WantToUnique :
	public Decision
{
	AICharacter* ai;
	virtual DecisionTreeNode* GetBranch();
public:
	void SetAI(AICharacter* ai_);
};

#endif // !WANTTOUNIQUE_H