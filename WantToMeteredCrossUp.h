#ifndef WANTTOMETEREDCROSSUP_H
#define WANTTOMETEREDCROSSUP_H


#include "Game/Decision Tree/Decision.h"
#include "AICharacter.h"
class WantToMeteredCrossUp :
	public Decision
{
	AICharacter* ai;
	virtual DecisionTreeNode* GetBranch();
public:
	void SetAI(AICharacter* ai_);
};

#endif // !WANTTOMETEREDCROSSUP_H
