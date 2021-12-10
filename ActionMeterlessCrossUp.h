#ifndef ACTIONMETERLESSCROSSUP_H
#define ACTIONMETERLESSCROSSUP_H


#include "Game/Decision Tree/Action.h"
#include "AICharacter.h"
class ActionMeterlessCrossUp :
	public Action
{
public:
	ActionMeterlessCrossUp();
	void SetAI(AICharacter* ai_) { ai = ai_; };
private:
	AICharacter* ai;
	virtual DecisionTreeNode* MakeDecision() override;

};
#endif // !ACTIONMETERLESSCROSS_H
