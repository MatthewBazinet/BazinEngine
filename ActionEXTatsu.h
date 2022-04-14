#ifndef ACTIONEXTATSU_H
#define ACTIONEXTATSU_H


#include "Game/Decision Tree/Action.h"
#include "AICharacter.h"
class ActionEXTatsu :
	public Action
{
public:
	ActionEXTatsu();
	void SetAI(AICharacter* ai_) { ai = ai_; };
private:
	AICharacter* ai;
	virtual DecisionTreeNode* MakeDecision() override;

};
#endif // !ACTIONEXTATSU_H
