#include "ActionFireball.h"

ActionFireball::ActionFireball()
{
	word = "Fireball";
}

DecisionTreeNode* ActionFireball::MakeDecision()
{
	ai->UseFireball();
	return this;
}
