#ifndef WANTTOFIREBALL_H
#define WANTTOFIREBALL_H


#include "Game/Decision Tree/Decision.h"
#include "AICharacter.h"
class WantToFireball :
	public Decision
{
	AICharacter* ai;
	virtual DecisionTreeNode* GetBranch();
public:
	void SetAI(AICharacter* ai_);
};

#endif // !WANTTOFIREBALL_H
