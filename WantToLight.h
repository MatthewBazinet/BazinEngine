#ifndef WANTTOLIGHT_H
#define WANTTOLIGHT_H


#include "Game/Decision Tree/Decision.h"
#include "AICharacter.h"
class WantToLight :
	public Decision
{
	AICharacter* ai;
	virtual DecisionTreeNode* GetBranch();
public:
	void SetAI(AICharacter* ai_);
};

#endif // !WANTTOLIGHT_H