#ifndef WANTTOEXTATSU_H
#define WANTTOEXTATSU_H


#include "Game/Decision Tree/Decision.h"
#include "AICharacter.h"
class WantToEXTatsu :
	public Decision
{
	AICharacter* ai;
	virtual DecisionTreeNode* GetBranch();
public:
	void SetAI(AICharacter* ai_);
};

#endif // !WANTTOEXTATSU_H