#ifndef FLOATDECISION_H
#define FLOATDECISION_H

#include "Decision.h"
#include "../TestChar.h"

class TestChar;

class FloatDecision : public Decision
{
private:
	float minValue;
	float maxValue;
	TestChar* testChar;

public:
	FloatDecision(float minValue_, float maxValue_);
	virtual ~FloatDecision() {};

	DecisionTreeNode* MakeDecision();
	DecisionTreeNode* TestValue();

	void SetMinValue(float minValue_) { minValue = minValue_; };
	void SetMaxValue(float maxValue_) { maxValue = maxValue_; };
	
	void SetChar(TestChar* testChar_) { testChar = testChar_; };
	TestChar* GetChar() { return testChar; };
};

#endif;