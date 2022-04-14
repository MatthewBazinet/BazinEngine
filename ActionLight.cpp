#include "ActionLight.h"

ActionLight::ActionLight()
{
	word = "Light";
}

DecisionTreeNode* ActionLight::MakeDecision()
{
	ai->UseLight();
	return this;
}
