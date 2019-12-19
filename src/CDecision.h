#pragma once

#include "CSymbols.h"
#include "COpponentModeling.h"

class CDecision
{
public:
	CDecision();

protected:
	double _decision;
	bool _gotcaught;
	bool _ibluffed;

public:
	void HandReset();
	int timesActed();
	double callExpectedValue();
	double allinExpectedValue(int villain_chair);

	double PreflopDecision();
	double postFlopDecision();
	double Decision();
	double GetDecisionAmount(double action_constant);
	ePlayerAction GetPlayerAction(double action_constant);
};

extern CDecision* g_decision;
