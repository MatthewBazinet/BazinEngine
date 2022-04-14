#ifndef WANTTOTATSU_H
#define WANTTOTATSU_H


#include "Game/Decision Tree/Decision.h"
#include "AICharacter.h"
class WantToTatsu :
	public Decision
{
	AICharacter* ai;
	virtual DecisionTreeNode* GetBranch();
public:
	void SetAI(AICharacter* ai_);
};

#endif // !WANTTOTATSU_H