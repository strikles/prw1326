#include "CExtractActions.h"
#include "CLogging.h"
#include "CSymbols.h"

#include <map>

void CExtractActions::ExtractActionsReset()
{
	_current_hand_info.NewHand();
	_opp_model.HandReset();

	_b_new_game		= true;
	_b_new_round	= true;
	_prev_betround	= k_undefined;
}

void CExtractActions::ExtractPreviousRoundActions()
{
	/////////////////////////////////////////////////
	// PICKUP MISSING ACTIONS FROM PREVIOUS ROUND  //
	// if it didn't come back to hero either:      //
	// a) hero folded                              //
	// b) only fold check or call possible         //
	/////////////////////////////////////////////////

	for (int ndx = g_symbols->get_userchair() + 1;; ndx++)
	{
		// VERIFY ME - HU + Dealer Chair
		int stop_chair = g_symbols->get_userchair();
		int chair_ndx = ndx % g_symbols->get_nchairs();

		if ( chair_ndx == stop_chair )
			break;

		if ( !_current_hand_info._player_actions[chair_ndx]._b_was_in_game )
			continue;

		int betround = g_symbols->get_betround();
		int prev_times_acted = _current_hand_info._times_acted[_prev_betround];
		double current_bet = g_symbols->get_currentbet(chair_ndx);
		double balance = g_symbols->get_balance(chair_ndx);

		// Folded previous betround
		if ( !is_active_bit(chair_ndx, g_symbols->get_playersplayingbits()) )
		{
			_current_hand_info.RecordPlayerAction(_prev_betround,
				chair_ndx,
				actionFold,
				_current_hand_info._player_actions[chair_ndx]._prev_bet[_prev_betround],
				balance);
		}
		// Checked
		else if ( IsEqual(_current_hand_info._player_actions[chair_ndx]._actions[_prev_betround][prev_times_acted]._balance, balance) )
		{
			_current_hand_info.RecordPlayerAction(_prev_betround,
				chair_ndx,
				actionCheck,
				_current_hand_info._amount_to_call[_prev_betround],
				balance);

			//_opp_model.ModelOpponent(chair_ndx, _prev_betround, actionCheck);
		}
		// Called
		else if ( _current_hand_info._player_actions[chair_ndx]._actions[_prev_betround][prev_times_acted]._balance > balance )
		{
			_current_hand_info.RecordPlayerAction(_prev_betround,
				chair_ndx,
				actionCall,
				_current_hand_info._amount_to_call[_prev_betround],
				balance);

			_opp_model.ModelOpponent(chair_ndx, _prev_betround, actionCall);
		}
	}
}

void CExtractActions::ExtractPreviousTimesActedActions()
{
	////////////////////////////////////////////
	// Extract Actions of players behind hero //
	////////////////////////////////////////////

	for (int ndx = g_symbols->get_userchair() + 1;; ndx++)
	{
		// VERIFY ME - HU + Dealer Chair
		int chair_ndx = ndx % g_symbols->get_nchairs();
		int stop_chair = (g_symbols->get_dealerchair() + 1) % g_symbols->get_nchairs();
		//int stop_chair = g_symbols->get_userchair();

		if ( chair_ndx == stop_chair )
			break;

		if ( !_current_hand_info._player_actions[chair_ndx]._b_was_in_game )
			continue;

		int betround = g_symbols->get_betround();
		int times_acted = _current_hand_info._times_acted[betround];
		double current_bet = g_symbols->get_currentbet(chair_ndx);
		double balance = g_symbols->get_balance(chair_ndx);

		// Folded previous times acted
		if ( current_bet < _current_hand_info._amount_to_call[betround] )
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionFold,
				_current_hand_info._player_actions[chair_ndx]._prev_bet[betround],
				balance);
		}
		// Checked
		else if ( IsEqual(_current_hand_info._player_actions[chair_ndx]._actions[betround][times_acted]._balance, balance) &&
			IsEqual(current_bet, _current_hand_info._player_actions[chair_ndx]._prev_bet[betround]) )
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionCheck,
				_current_hand_info._amount_to_call[betround],
				balance);

			//_opp_model.ModelOpponent(chair_ndx, betround, actionCheck);
		}
		// Call
		else if ( IsEqual(current_bet, _current_hand_info._amount_to_call[betround] ) ||
			( IsEqual(balance, 0) && current_bet > epsilon ) )
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionCall,
				_current_hand_info._amount_to_call[betround],
				balance);

			_opp_model.ModelOpponent(chair_ndx, betround, actionCall);
		}
		// Raise
		else if ( current_bet > _current_hand_info._amount_to_call[betround] )
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionBetRaise,
				current_bet,
				balance);

			_opp_model.ModelOpponent(chair_ndx, betround, actionBetRaise);
		}
	}
}


void CExtractActions::ExtractCurrentActions()
{
	//////////////////////////////////////////////
	// Extract Actions of players ahead of hero //
	//////////////////////////////////////////////

	for (size_t ndx = _current_hand_info._current_actor + 1;; ndx++)
	{
		int chair_ndx = ndx % g_symbols->get_nchairs();

		if (chair_ndx == g_symbols->get_userchair())
			break;

		if (!_current_hand_info._player_actions[chair_ndx]._b_was_in_game)
			continue;

		int betround = g_symbols->get_betround();
		int prev_times_acted = _current_hand_info._times_acted[_prev_betround];
		double current_bet = g_symbols->get_currentbet(chair_ndx);
		double balance = g_symbols->get_balance(chair_ndx);

		/*
		g_log->WriteLog(eSeverityInfo, eCatExtractActions, "current_actor:%d cb:%g pb:%g\n",
			ndx,
			current_bet,
			_current_hand_info._amount_to_call[betround]);
		*/

		// Fold
		if ( current_bet < _current_hand_info._amount_to_call[betround] )
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionFold,
				current_bet,
				balance);
		}
		// Checked
		else if ( IsEqual(current_bet, _current_hand_info._amount_to_call[betround]) &&
			IsEqual(current_bet, _current_hand_info._player_actions[chair_ndx]._prev_bet[betround]) )
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionCheck,
				current_bet,
				balance);

			//_opp_model.ModelOpponent(chair_ndx, betround, actionCheck);
		}
		// Call - player may have less than call amount and go all-in
		else if ( ( IsEqual(current_bet, _current_hand_info._amount_to_call[betround]) && 
			_current_hand_info._amount_to_call[betround] > epsilon ) || 
			( IsEqual(balance, .0) && current_bet > epsilon ) )
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionCall,
				current_bet,
				balance);

			_opp_model.ModelOpponent(chair_ndx, betround, actionCall);
		}
		// Raise
		else if ( current_bet > _current_hand_info._amount_to_call[betround] )
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionBetRaise,
				current_bet,
				balance);

			_opp_model.ModelOpponent(chair_ndx, betround, actionBetRaise);
		}
	}
}

void CExtractActions::ExtractActionsNewGame()
{
	//////////////
	// NEW GAME //
	//////////////

	g_log->WriteLog(eSeverityInfo, eCatInfo, "Starting New Hand\n");
	_current_hand_info.NewHand();
	_opp_model.HandReset();

	////////////////////////
	// We Know the Blinds //
	////////////////////////

	// account for missing small blind
	if(g_symbols->get_smallblindchair() != k_undefined)
	{
		_current_hand_info.RecordPlayerAction(g_symbols->get_betround(),
			g_symbols->get_smallblindchair(),
			actionPostedSB,
			g_symbols->get_sblind(),
			g_symbols->get_balance(g_symbols->get_smallblindchair()));
	}
	_current_hand_info.RecordPlayerAction(g_symbols->get_betround(),
		g_symbols->get_bigblindchair(),
		actionPostedBB,
		g_symbols->get_bblind(),
		g_symbols->get_balance(g_symbols->get_bigblindchair()));

	//////////////////////////////////
	// Remaining actions up to hero //
	//////////////////////////////////

	ExtractCurrentActions();

	_b_new_game = false;
}

void CExtractActions::ExtractActionsNewRound()
{
	///////////////
	// NEW ROUND //
	///////////////

	g_log->WriteLog(eSeverityInfo, eCatInfo, "Picking missed Actions\n");
	ExtractPreviousRoundActions();

	g_log->WriteLog(eSeverityInfo, eCatInfo, "Starting New Round\n");
	_current_hand_info.NewBettingRound();
	ExtractCurrentActions();
}

void CExtractActions::ExtractRemainingActions()
{
	g_log->WriteLog(eSeverityInfo, eCatInfo, "Picking missed Actions\n");
	ExtractPreviousTimesActedActions();

	g_log->WriteLog(eSeverityInfo, eCatInfo, "Extracting current Round\n");
	ExtractCurrentActions();
}

void CExtractActions::ExtractActions()
{
	_b_new_round = (g_symbols->get_betround() > ePreflop && (g_symbols->get_betround() != _prev_betround));

	g_log->WriteLog(eSeverityInfo, eCatGeneral, "Board: %c%c %c%c %c%c %c%c %c%c\n",
		Rank_ASC(g_symbols->get_$$cr0()), Suit52_ASC(g_symbols->get_$$cs0()),
		Rank_ASC(g_symbols->get_$$cr1()), Suit52_ASC(g_symbols->get_$$cs1()),
		Rank_ASC(g_symbols->get_$$cr2()), Suit52_ASC(g_symbols->get_$$cs2()),
		Rank_ASC(g_symbols->get_$$cr3()), Suit52_ASC(g_symbols->get_$$cs3()),
		Rank_ASC(g_symbols->get_$$cr4()), Suit52_ASC(g_symbols->get_$$cs4())
	);
	g_log->WriteLog(eSeverityInfo, eCatGeneral, "Player Cards: %c%c %c%c\n",
		Rank_ASC(g_symbols->get_$$pr0()), Suit52_ASC(g_symbols->get_$$ps0()),
		Rank_ASC(g_symbols->get_$$pr1()), Suit52_ASC(g_symbols->get_$$ps1())
	);

	g_log->WriteLog(eSeverityInfo, eCatGeneral, "Pokervalcommon: %u %s\n",
		g_symbols->get_pokervalcommon(), Pokerval_ASC(g_symbols->get_pokervalcommon())
	);
	g_log->WriteLog(eSeverityInfo, eCatGeneral, "Pokerval      : %u %s\n",
		g_symbols->get_pokerval(), Pokerval_ASC(g_symbols->get_pokerval())
	);

	if (_b_new_game)
		ExtractActionsNewGame();
	else if (_b_new_round)
		ExtractActionsNewRound();
	else
		ExtractRemainingActions();

	_prev_betround = g_symbols->get_betround();
}
