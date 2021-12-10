#ifndef ACTIONMETEREDCROSSUP_H
#define ACTIONMETEREDCROSSUP_H


#include "Game/Decision Tree/Action.h"
#include "AICharacter.h"
class ActionMeteredCrossUp :
	public Action
{
public:
	ActionMeteredCrossUp();
	void SetAI(AICharacter* ai_) { ai = ai_; };
private:
	AICharacter* ai;
	virtual DecisionTreeNode* MakeDecision() override;

};
#endif // !ACTIONMETEREDCROSS_H
