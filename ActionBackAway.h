#ifndef ACTIONBACKAWAY_H
#define ACTIONBACKAWAY_H


#include "Game/Decision Tree/Action.h"
#include "AICharacter.h"
class ActionBackAway :
	public Action
{
public:
	ActionBackAway();
	void SetAI(AICharacter* ai_) { ai = ai_; };
private:
	AICharacter* ai;
	virtual DecisionTreeNode* MakeDecision() override;

};
#endif // !ACTIONBACKAWAY_H
