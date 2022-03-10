#ifndef ACTIONMOVETOWARDS_H
#define ACTIONMOVETOWARDS_H


#include "Game/Decision Tree/Action.h"
#include "AICharacter.h"
class ActionMoveTowards :
	public Action
{
public:
	ActionMoveTowards();
	void SetAI(AICharacter* ai_) { ai = ai_; };
private:
	AICharacter* ai;
	virtual DecisionTreeNode* MakeDecision() override;

};
#endif // !ACTIONMOVETOWARDS_H
