#ifndef ACTIONMEDIUM_H
#define ACTIONMEDIUM_H


#include "Game/Decision Tree/Action.h"
#include "AICharacter.h"
class ActionMedium :
	public Action
{
public:
	ActionMedium();
	void SetAI(AICharacter* ai_) { ai = ai_; };
private:
	AICharacter* ai;
	virtual DecisionTreeNode* MakeDecision() override;

};
#endif // !ACTIONMEDIUM_H
