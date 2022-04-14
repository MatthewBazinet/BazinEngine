#ifndef ACTIONTATSU_H
#define ACTIONTATSU_H


#include "Game/Decision Tree/Action.h"
#include "AICharacter.h"
class ActionTatsu :
	public Action
{
public:
	ActionTatsu();
	void SetAI(AICharacter* ai_) { ai = ai_; };
private:
	AICharacter* ai;
	virtual DecisionTreeNode* MakeDecision() override;

};
#endif // !ACTIONTATSU_H
