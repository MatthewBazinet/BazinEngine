#ifndef WANTTOEXFIREBALL_H
#define WANTTOEXFIREBALL_H


#include "Game/Decision Tree/Decision.h"
#include "AICharacter.h"
class WantToEXFireball :
	public Decision
{
	AICharacter* ai;
	virtual DecisionTreeNode* GetBranch();
public:
	void SetAI(AICharacter* ai_);
};

#endif // !WANTTOEXFIREBALL_H
