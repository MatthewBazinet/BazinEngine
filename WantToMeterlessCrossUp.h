#ifndef WANTTOMETERLESSCROSSUP_H
#define WANTTOMETERLESSCROSSUP_H


#include "Game/Decision Tree/Decision.h"
#include "AICharacter.h"
class WantToMeterlessCrossUp :
	public Decision
{
	AICharacter* ai;
	virtual DecisionTreeNode* GetBranch();
public:
	void SetAI(AICharacter* ai_);
};

#endif // !WANTTOMETERLESSCROSSUP_H
