#ifndef ACTIONHEAVY_H
#define ACTIONHEAVY_H


#include "Game/Decision Tree/Action.h"
#include "AICharacter.h"
class ActionHeavy :
	public Action
{
public:
	ActionHeavy();
	void SetAI(AICharacter* ai_) { ai = ai_; };
private:
	AICharacter* ai;
	virtual DecisionTreeNode* MakeDecision() override;

};
#endif // !ACTIONHEAVY_H
