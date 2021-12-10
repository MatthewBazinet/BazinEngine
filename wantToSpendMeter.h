#ifndef WANTTOSPENDMETER_H
#define WANTTOSPENDMETER_H


#include "Game/Decision Tree/Decision.h"
#include "AICharacter.h"
class WantToSpendMeter :
	public Decision
{
	AICharacter* ai;
	virtual DecisionTreeNode* GetBranch();
public:
	void SetAI(AICharacter* ai_);
};

#endif // !WANTTOSPENDMETER_H