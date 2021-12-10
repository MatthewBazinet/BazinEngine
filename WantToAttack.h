#ifndef WANTTOATTACK_H
#define WANTTOATTACK_H


#include "Game/Decision Tree/Decision.h"
#include "AICharacter.h"
class WantToAttack :
	public Decision
{
	AICharacter* ai;
	virtual DecisionTreeNode* GetBranch();
public:
	void SetAI(AICharacter* ai_);
};

#endif // !WANTTOATTACK_H
