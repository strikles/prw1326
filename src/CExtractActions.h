#pragma once

#include "CHandHistory.h"
#include "COpponentModeling.h"

#include <map>

class CExtractActions
{
public:
	// State Variables
	bool			_b_new_game;
	bool			_b_new_round;
	bool			_is_heads_up;
	bool			_hero_in_blinds;
	int				_prev_betround;
	CHandHistory	_current_hand_info;
	COpponentModeling _opp_model;

public:

	//std::map<int, int> CExtractActions::SortPlayers();

	void ExtractActionsReset();
	void ExtractPreviousRoundActions();
	void ExtractPreviousTimesActedActions();
	void ExtractCurrentActions();
	
	void ExtractActionsNewGame();
	void ExtractActionsNewRound();
	void ExtractRemainingActions();

	void ExtractActions();
};

extern CExtractActions* g_extract_actions;