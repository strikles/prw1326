#include "CDecision.h"

#include "CLogging.h"
#include "CSymbols.h"
#include "CExtractActions.h"

CDecision::CDecision() : 
	_decision(.0)
{
}

void CDecision::HandReset()
{
	_decision = .0;
}

int CDecision::timesActed()
{
	return g_symbols->get_didcall() +
		g_symbols->get_didchec() +
		g_symbols->get_didrais() +
		g_symbols->get_didbetsize();
}

double CDecision::callExpectedValue()
{
	double ev = (g_symbols->get_prwin() + g_symbols->get_prtie()/g_symbols->get_nplayersplaying())*g_symbols->get_pot() - g_symbols->get_prlos()*g_symbols->get_call();
	g_log->WriteLog(eSeverityInfo, eCatDecision, "Call expected value: %g\n", ev);

	return ev;
}

double CDecision::allinExpectedValue(int villain_chair)
{
	if (villain_chair == -1)
		return 0;

	// correct for 4 bet vs 3 bet vs raise
	double villain_folds = (g_symbols->get_betround() == ePreflop ? g_symbols->_pt.get_pt_fold_to_3bet(villain_chair) : g_symbols->_pt.get_pt_postflop_fold_to_3bet(villain_chair));
	g_log->WriteLog(eSeverityInfo, eCatDecision, "villain_folds: %g\n", villain_folds);
	if (villain_folds == -1)
		villain_folds = 0.1; // 0.2 0.5 0.7
	double fold_ev = villain_folds*g_symbols->get_pot();

	double villain_calls_we_win_ev = (1 - villain_folds)*g_symbols->get_prwin()*(g_symbols->get_pot() + min(g_symbols->get_balance(g_symbols->get_userchair()), g_symbols->get_balance(villain_chair)));
	double villain_calls_we_lose_ev = (1 - villain_folds)*g_symbols->get_prlos()*min(g_symbols->get_balance(g_symbols->get_userchair()), g_symbols->get_balance(villain_chair));

	return fold_ev + villain_calls_we_win_ev - villain_calls_we_lose_ev;
}

double CDecision::PreflopDecision()
{
	// early position

	// middle position

	// late position

	// blinds
	double decision		= 0;

	double phr			= (170.0 - g_symbols->get_handrank169())/169.0;
	double current_bet	= g_symbols->get_currentbet(g_symbols->get_userchair());
	double balance		= g_symbols->get_balance(g_symbols->get_userchair());
	double call			= g_symbols->get_call();
	double pot			= g_symbols->get_pot();
	double bblind		= g_symbols->get_bblind();
	double min_bet		= max(2*call, bblind);
	double nplayers		= g_symbols->get_nplayersplaying();
	int times_acted		= timesActed();

	g_log->WriteLog(eSeverityInfo, eCatDecision, "phr:%f\n", phr);

	// 88+ 0.964 2pl
	// 88+ 0.887 6pl
	if (0.964 < phr)
	{
		if (times_acted == 0)
		{
			decision = (min_bet > 4*bblind ? GetSymbol("RaisePot") : 4);
		}
		else if(times_acted == 1)
		{
			decision = GetSymbol("RaiseTwoPot");
		}
		else
		{
			decision = GetSymbol("RaiseMax");
		}
	}
	// 55+ 0.863 2pl
	// 55+ 0.704 6pl
	else if (0.863 < phr && call <= 13 * bblind)
	{
		if (times_acted == 0 && IsEqual(call, .0))
		{
			decision = (min_bet > 4*bblind ? GetSymbol("RaisePot") : 4);
		}
		else
		{
			decision = GetSymbol("Call");
		}
	}
	// 22+ 0.526 2pl
	// 22+ 0.473 6pl
	else if (0.526 < phr && call <= 4*bblind)
	{
		decision = GetSymbol("Call");
	}

	_gotcaught = false, _ibluffed = false;
	g_log->WriteLog(eSeverityInfo, eCatDecision, ">>> PreFlop decision -> %g\n", decision);

	return decision;
}

double CDecision::postFlopDecision()
{
	double decision		= 0;
	double current_bet	= g_symbols->get_currentbet(g_symbols->get_userchair());
	double balance		= g_symbols->get_balance(g_symbols->get_userchair());
	double call			= g_symbols->get_call();
	double pot			= g_symbols->get_pot();
	double bblind		= g_symbols->get_bblind();
	double min_bet		= max(2 * call, bblind);
	double prwin		= g_symbols->get_prwin();
	double inv			= 1.0 / g_symbols->get_nplayersplaying();

	int times_acted = timesActed();

	if (_ibluffed == true && times_acted > 0)
		_gotcaught = true;

	g_log->WriteLog(eSeverityInfo, eCatDecision, " -> prwin:%g inv:%g prwin-inv:%g\n", 
		prwin, 
		inv, 
		prwin - inv);

	double monster_prwin	= g_symbols->get_nplayersplaying() <= 6 ? 0.34 : 0.42;
	double bluff_prwin		= g_symbols->get_nplayersplaying() == 2 ? 0.1 : 0.15;

	if (monster_prwin < (prwin - inv))
	{
		if (times_acted == 0)
			decision = (min_bet > bblind ? GetSymbol("RaiseHalfPot") : GetSymbol("RaiseMin"));
		if (times_acted == 1)
			decision = GetSymbol("RaiseTwoPot");
		else
			decision = GetSymbol("RaiseMax");
	}
	else if (bluff_prwin < (prwin - inv))
	{
		if (times_acted == 0 && IsEqual(0, call) && false == _gotcaught)
		{
			decision = GetSymbol("RaiseHalfPot");
			_ibluffed = true;
		}
		else if (call < callExpectedValue())
		{
			decision = GetSymbol("Call");
		}
	}
	else if (call < callExpectedValue())
	{
		decision = GetSymbol("Call");
	}

	g_log->WriteLog(eSeverityInfo, eCatDecision, ">>> PostFlop decision -> %g\n", decision);

	return decision;
}

double CDecision::GetDecisionAmount(double action_constant)
{
	double current_bet	= g_symbols->get_currentbet(g_symbols->get_userchair());
	double balance		= g_symbols->get_balance(g_symbols->get_userchair());
	double call			= g_symbols->get_call();
	double pot			= g_symbols->get_pot();
	double bblind		= g_symbols->get_bblind();

	double amount = 0;
	if (IsEqual(action_constant, 0))
		amount = current_bet;
	else if (action_constant > 0)
		amount = current_bet + call + action_constant*bblind;
	else if (IsEqual(action_constant, GetSymbol("RaiseMax")))
		amount = current_bet + balance;
	else if (IsEqual(action_constant, GetSymbol("RaiseTwoPot")))
		amount = current_bet + call + 2*pot;
	else if (IsEqual(action_constant, GetSymbol("RaisePot")))
		amount = current_bet + call + pot;
	else if (IsEqual(action_constant, GetSymbol("RaiseHalfPot")))
		amount = current_bet + call + pot/2;
	else if (IsEqual(action_constant, GetSymbol("RaiseMin")))
		amount = current_bet + call + max(2*call, bblind);
	else if (IsEqual(action_constant, GetSymbol("Call")))
		amount = current_bet + call;

	return amount;
}

ePlayerAction CDecision::GetPlayerAction(double action_constant)
{
	ePlayerAction eDecision = actionFold;
	if (IsEqual(action_constant, 0))
	{
		if (IsEqual(g_symbols->get_call(), 0))
			eDecision = actionCheck;
	}
	else if (IsEqual(action_constant, GetSymbol("Call")))
	{
		eDecision = actionCall;
		if (IsEqual(g_symbols->get_call(), 0))
			eDecision = actionCheck;
	}
	else if (action_constant > 0 ||
		IsEqual(action_constant, GetSymbol("RaiseMax")) ||
		IsEqual(action_constant, GetSymbol("RaiseTwoPot")) ||
		IsEqual(action_constant, GetSymbol("RaisePot")) ||
		IsEqual(action_constant, GetSymbol("RaiseHalfPot")) ||
		IsEqual(action_constant, GetSymbol("RaiseMin")))
	{
		eDecision = actionBetRaise;
	}

	return eDecision;
}

double CDecision::Decision()
{
	_decision = 0;
	switch (g_symbols->get_betround())
	{
		case ePreflop:
			_decision = PreflopDecision();
			break;
		case eFlop:
			_decision = postFlopDecision();
			break;
		case eTurn:
			_decision = postFlopDecision();
			break;
		case eRiver:
			_decision = postFlopDecision();
			break;
		default:
			break;
	}

	// Record Bot Decision to set _current_actor in CHandHistory
	g_extract_actions->_current_hand_info.RecordPlayerAction(g_symbols->get_betround(),
		g_symbols->get_userchair(),
		GetPlayerAction(_decision),
		GetDecisionAmount(_decision),
		g_symbols->get_balance(g_symbols->get_userchair()));

	return _decision;
}