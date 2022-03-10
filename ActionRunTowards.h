#ifndef ACTIONRUNTOWARDS_H
#define ACTIONRUNTOWARDS_H


#include "Game/Decision Tree/Action.h"
#include "AICharacter.h"
class ActionRunTowards :
	public Action
{
public:
	ActionRunTowards();
	void SetAI(AICharacter* ai_) { ai = ai_; };
private:
	AICharacter* ai;
	virtual DecisionTreeNode* MakeDecision() override;

};
#endif // !ACTIONMOVETOWARDS_H
