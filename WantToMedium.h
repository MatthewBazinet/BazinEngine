#ifndef WANTTOMEDIUM_H
#define WANTTOMEDIUM_H


#include "Game/Decision Tree/Decision.h"
#include "AICharacter.h"
class WantToMedium :
	public Decision
{
	AICharacter* ai;
	virtual DecisionTreeNode* GetBranch();
public:
	void SetAI(AICharacter* ai_);
};

#endif // !WANTTOMEDIUM_H