#ifndef ACTIONFIREBALL_H
#define ACTIONFIREBALL_H


#include "Game/Decision Tree/Action.h"
#include "AICharacter.h"
class ActionFireball :
	public Action
{
public:
	ActionFireball();
	void SetAI(AICharacter* ai_) { ai = ai_; };
private:
	AICharacter* ai;
	virtual DecisionTreeNode* MakeDecision() override;

};
#endif // !ACTIONFIREBALL_H
