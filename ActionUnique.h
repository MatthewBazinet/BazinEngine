#ifndef ACTIONUNIQUE_H
#define ACTIONUNIQUE_H


#include "Game/Decision Tree/Action.h"
#include "AICharacter.h"
class ActionUnique :
	public Action
{
public:
	ActionUnique();
	void SetAI(AICharacter* ai_) { ai = ai_; };
private:
	AICharacter* ai;
	virtual DecisionTreeNode* MakeDecision() override;

};
#endif // !ACTIONUNIQUE_H
