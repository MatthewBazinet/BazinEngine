#ifndef ACTIONEXFIREBALL_H
#define ACTIONEXFIREBALL_H


#include "Game/Decision Tree/Action.h"
#include "AICharacter.h"
class ActionEXFireball :
	public Action
{
public:
	ActionEXFireball();
	void SetAI(AICharacter* ai_) { ai = ai_; };
private:
	AICharacter* ai;
	virtual DecisionTreeNode* MakeDecision() override;

};
#endif // !ACTIONEXFIREBALL_H
