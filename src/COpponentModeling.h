#pragma once

#include <string>
#include <set>

#include "magicNumbers.h"

struct sprw1326_chair
{
	//indicates weighting level for 'always consider'
	int	level;
	//max index into weight array - used for computational efficiency
	int	limit;
	//if non-zero no weighting will be applied to this chair
	int	ignore;
	//higher ranked card number in pocket cards
	int	rankhi[1326];
	//lower ranked card number in pocket cards
	int	ranklo[1326];
	//the significance value for this hand
	int	weight[1326];
	//for future reference 
	double	scratch;
};

struct sprw1326
{
	//unless set to 1326 the normal OH prwin will be used
	int	useme;
	//unless set to 1326 the normal OH prwin will be used pre-flop
	int	preflop;
	//unless set to 1326 the callback function will not be invoked
	int	usecallback;
	//if enabled will be invoked before the prwin calculation pass
	double(*prw_callback)();
	//for future reference
	double scratch;
	//if non-zero no weighting will be applied if a chair has put nothing in the pot
	int	bblimp;
	//will be precalculated by OH at startup - convenience values
	sprw1326_chair vanilla_chair;
	//structures for each chair
	sprw1326_chair chair[10]; 
};

class COpponentModeling
{
public:
	COpponentModeling();

public:
	sprw1326* _prw1326;
	int _round_trigger;
	bool _hand_reset;

	std::set<int> prw1326_preflop[k_max_chairs];
	std::set<int> prw1326_straights[k_max_chairs];
	std::set<int> prw1326_flushes[k_max_chairs];
	std::set<int> prw1326_pairs[k_max_chairs];

	// vectors of hole card groups filled at init

public:
	void Prw1326AddListElement(int player_ndx, int r1, int r2, int s1, int s2, int weight);
	int Prw1326WeightListElement(int player_ndx, int r1, int r2, int s1, int s2, int weight);
	int Prw1326GetListElement(int player_ndx, int r1, int r2, int s1, int s2);
	void Prw1326ChangeWeightOnList(int player_ndx, int old_weight, int new_weight);
	
	void Prw1326AddPocketPair(int player_ndx, int r1, int weight);
	void Prw1326AddOffSuit(int player_ndx, int r1, int r2, int weight);
	void Prw1326AddSuit(int player_ndx, int r1, int r2, int weight);

	void Prw1326GetPocketPair(int player_ndx, int r1);
	void Prw1326GetOffSuit(int player_ndx, int r1, int r2);
	void Prw1326GetSuit(int player_ndx, int r1, int r2);

	void GiveVillainStraights(int playerchairt);
	void GiveVillainFlushes(int playerchair);
	void GiveVillainPairs(int playerchair);
	void Prw1326PostflopFiltered(int playerchair, int weight);
	void Prw1326PostflopNaive(int playerchair, int weight);
	void Prw1326Postflop(int playerchair, int weight);

	void PrwSetPreflopBottomList(int player_ndx, double exclude_pct, int weight);
	void PrwSetPreflopMiddleList(int player_ndx, double play_pct, double exclude_pct, int weight);
	void PrwSetPreflopTopList(int player_ndx, double play_pct, int weight);
	int  ModelOpponent(int chair_ndx,int betround, int action);

	void init(int listnum, int weight);
	void HandReset();
	void PrwLogHandlist(int handnumber, int userchair, int betround, int log_param);
	void CreateDir(std::string dirname);
};

//extern COpponentModeling* g_opponent_modeling;