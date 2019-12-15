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
	return g_symbols->get_didcall(g_symbols->get_betround()) +
		g_symbols->get_didchec(g_symbols->get_betround()) +
		g_symbols->get_didrais(g_symbols->get_betround()) +
		g_symbols->get_didbetsize(g_symbols->get_betround());
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
	double decision = 0.0;

	double phr			= (169.0 - g_symbols->get_handrank169() + 1.0)/169.0;
	double current_bet	= g_symbols->get_currentbet(g_symbols->get_userchair());
	double balance		= g_symbols->get_balance(g_symbols->get_userchair());
	double call			= g_symbols->get_call();
	double pot			= g_symbols->get_pot();
	double bblind		= g_symbols->get_bblind();
	double min_bet		= max(2*call, bblind);
	double nplayers		= g_symbols->get_nplayersplaying();
	int times_acted		= timesActed();

	g_log->WriteLog(eSeverityInfo, eCatDecision, "phr:%f\n", phr);

	if(2 < nplayers)
	{
		// 88+ 0.964 2pl
		// 88+ 0.887 6pl
		if (0.887 < phr)
		{
			if (times_acted <= 2)
			{
				decision = call + max(pot, 4 * bblind);
			}
			else
			{
				decision = balance;
			}
		}
		// 55+ 0.863 2pl
		// 55+ 0.704 6pl
		else if (0.704 < phr && call <= 13 * bblind)
		{
			if (times_acted == 0 && IsEqual(call, .0))
			{
				decision = call + max(pot, 4 * bblind);
			}
			else
			{
				decision = call;
			}
		}
	}
	else if(2 == nplayers)
	{
		/*
		if (0 < allinExpectedValue(g_symbols->get_headsupchair()) && balance < 50*bblind)
		{
			decision = balance;
		}
		*/
		// 88+ 0.964 2pl
		// 88+ 0.887 6pl
		if (0.964 < phr)
		{
			if (times_acted <= 2)
			{
				decision = call + max(pot, 4 * bblind);
			}
			else
			{
				decision = balance;
			}
		}
		// 55+ 0.863 2pl
		// 55+ 0.704 6pl
		else if (0.863 < phr && call <= 13 * bblind)
		{
			if (times_acted == 0 && IsEqual(call, .0))
			{
				decision = call + max(pot, 4 * bblind);
			}
			else
			{
				decision = call;
			}
		}
		// 22+ 0.526 2pl
		// 22+ 0.473 6pl
		else if (0.526 < phr && call <= 4*bblind)
		{
			decision = call;
		}
	}

	_gotcaught = false, _ibluffed = false;
	decision = current_bet + min(balance, decision);
	g_log->WriteLog(eSeverityInfo, eCatDecision, ">>> PreFlop decision -> %g\n", decision);

	return decision;
}

double CDecision::postFlopDecision()
{
	double decision		= 0.0;
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

	double monster_prwin = g_symbols->get_nplayersplaying() <= 6 ? 0.34 : 0.42;
	double bluff_prwin = g_symbols->get_nplayersplaying() == 2 ? 0.1 : 0.15;

	/*
	if (0 < allinExpectedValue(g_symbols->get_headsupchair()) && g_symbols->get_nplayersplaying() == 2 && balance < 50*bblind)
	{
		decision = balance;
	}
	*/
	if (monster_prwin < (prwin - inv))
	{
		if (times_acted <= 2)
			decision = call + max(min_bet, pot);
		else
			decision = balance;
	}
	else if (bluff_prwin < (prwin - inv))
	{
		if (false == _gotcaught && IsEqual(0, call) && times_acted == 0)
		{
			decision = call + max(min_bet, pot/2);
			_ibluffed = true;
		}
		else if (call < callExpectedValue())
		{
			decision = call;
		}
	}
	else if (call < callExpectedValue())
	{
		decision = call;
	}

	decision = current_bet + min(balance, decision);
	g_log->WriteLog(eSeverityInfo, eCatDecision, ">>> PostFlop decision -> %g\n", decision);

	return decision;
}

double CDecision::Decision()
{
	double current_bet	= g_symbols->get_currentbet(g_symbols->get_userchair());
	double balance		= g_symbols->get_balance(g_symbols->get_userchair());
	double call			= g_symbols->get_call();
	double bblind		= g_symbols->get_bblind();

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

	// Record Bot Decision to set _current_actor in CHandHistory, etc...
	ePlayerAction eDecision = actionFold;
	if (IsEqual(_decision, current_bet))
	{
		if (IsEqual(call , 0))
			eDecision = actionCheck;
		else
			eDecision = actionFold;
	}
	else if (IsEqual(call + current_bet, _decision))
		eDecision = actionCall;
	else
		eDecision = actionBetRaise;

	g_extract_actions->_current_hand_info.RecordPlayerAction(g_symbols->get_betround(),
		g_symbols->get_userchair(),
		eDecision,
		_decision,
		balance);

	// heads-up
	if(g_symbols->get_nplayersplaying() == 2)
	{
		g_log->WriteLog(eSeverityError, eCatDecision, ">>> Decision -> %s [Call:%g All-In EV:%g Prwin:%g]\n",
			str_player_action[eDecision],
			call,
			allinExpectedValue(g_symbols->get_headsupchair()),
			g_symbols->get_prwin());
	}

	return _decision;
}