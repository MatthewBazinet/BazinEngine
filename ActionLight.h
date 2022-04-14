#ifndef ACTIONLIGHT_H
#define ACTIONLIGHT_H


#include "Game/Decision Tree/Action.h"
#include "AICharacter.h"
class ActionLight :
	public Action
{
public:
	ActionLight();
	void SetAI(AICharacter* ai_) { ai = ai_; };
private:
	AICharacter* ai;
	virtual DecisionTreeNode* MakeDecision() override;

};
#endif // !ACTIONLIGHT_H
