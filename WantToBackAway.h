#ifndef WANTTOBACKAWAY_H
#define WANTTOBACKAWAY_H


#include "Game/Decision Tree/Decision.h"
#include "AICharacter.h"
class WantToBackAway :
	public Decision
{
	AICharacter* ai;
	virtual DecisionTreeNode* GetBranch();
public:
	void SetAI(AICharacter* ai_);
};

#endif // !WANTTOBACKAWAY_H
