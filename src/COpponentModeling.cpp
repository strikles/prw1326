#include "COpponentModeling.h"

#include "CLogging.h"
#include "CSymbols.h"
#include "CExtractActions.h"
#include "magicNumbers.h"
#include "util.h"

#include <conio.h>
#include <iostream>
#include <vector>

#define UNLEN 256

COpponentModeling::COpponentModeling():
	_round_trigger(0)
{
	HandReset();
}

void COpponentModeling::HandReset()
{
	_prw1326 = (sprw1326*)GetPrw1326();
	//////////////////////
	//ACTIVATING PRW    
	//////////////////////
	_prw1326->preflop = 1326;
	_prw1326->useme = 1326;
	_hand_reset = true;

	for (size_t chair_ndx = 0; chair_ndx < k_max_chairs; chair_ndx++)
	{
		while (!prw1326_preflop[chair_ndx].empty())
		{
			prw1326_preflop[chair_ndx].erase(prw1326_preflop[chair_ndx].begin());
		}
		while (!prw1326_flushes[chair_ndx].empty())
		{
			prw1326_flushes[chair_ndx].erase(prw1326_flushes[chair_ndx].begin());
		}
		while (!prw1326_pairs[chair_ndx].empty())
		{
			prw1326_pairs[chair_ndx].erase(prw1326_pairs[chair_ndx].begin());
		}
		while (!prw1326_straights[chair_ndx].empty())
		{
			prw1326_straights[chair_ndx].erase(prw1326_straights[chair_ndx].begin());
		}
	}

	for (size_t playerchair = 0; playerchair < k_max_chairs; playerchair++)
	{
		init(playerchair, 128);
	}
}
                              
/////////////////////////////////////////////////////    
// Generic support functions   
/////////////////////////////////////////////////////
void COpponentModeling::Prw1326AddListElement(int player_ndx, int r1, int r2, int s1, int s2, int weight)
{
	/*
	adds hand to prw list
	*/
	int c1 = r1 + s1;
	int c2 = r2 + s2;
	int lim = _prw1326->chair[player_ndx].limit;

	if (c1 > c2)
	{
		_prw1326->chair[player_ndx].ranklo[lim] = c1;
		_prw1326->chair[player_ndx].rankhi[lim] = c2;
		//_cprintf("set %d %d for ndx: %d with weight: %d\n", c1, c2, lim, weight);
	}
	else
	{
		_prw1326->chair[player_ndx].ranklo[lim] = c2;
		_prw1326->chair[player_ndx].rankhi[lim] = c1;
		//_cprintf("set %d %d for ndx: %d with weight: %d\n", c1, c2, lim, weight);
	}

	_prw1326->chair[player_ndx].weight[lim] = weight;
	_prw1326->chair[player_ndx].limit++;
}

int COpponentModeling::Prw1326WeightListElement(int player_ndx, int r1, int r2, int s1, int s2, int weight)
{
	/*
	changes weight for specified hand with old_weight to new_weight
	*/
	int c1 = r1 + s1;
	int c2 = r2 + s2;
	int found_num = k_undefined;
	
	for (int p = 0; p < _prw1326->chair[player_ndx].limit; p++)
	{
		bool cond = false;
		if (c1 > c2)
			cond = _prw1326->chair[player_ndx].ranklo[p] == c1 && _prw1326->chair[player_ndx].rankhi[p] == c2;
		else
			cond = _prw1326->chair[player_ndx].ranklo[p] == c2 && _prw1326->chair[player_ndx].rankhi[p] == c1;

		if (cond)
		{
			found_num = p;
			break;
		}
	}

	if (found_num != k_undefined)
	{
		_prw1326->chair[player_ndx].weight[found_num] = weight;
		//_cprintf("Resetting weight for hand %d - %d\n", found_num, _prw1326->chair[player_ndx].weight[found_num]);
	}
	else
	{
		_cprintf("could not find list element for %d|%d %d|%d\n", r1, s1, r2, s2);
	}

	return found_num;
}

int COpponentModeling::Prw1326GetListElement(int player_ndx, int r1, int r2, int s1, int s2)
{
	/*
	changes weight for specified hand with old_weight to new_weight
	*/
	int c1 = r1 + s1;
	int c2 = r2 + s2;
	int found_num = k_undefined;

	for (int p = 0; p < _prw1326->chair[player_ndx].limit; p++)
	{
		bool cond = false;
		if (c1 > c2)
			cond = _prw1326->chair[player_ndx].ranklo[p] == c1 && _prw1326->chair[player_ndx].rankhi[p] == c2;
		else
			cond = _prw1326->chair[player_ndx].ranklo[p] == c2 && _prw1326->chair[player_ndx].rankhi[p] == c1;

		if (cond)
		{
			found_num = p;
			break;
		}
	}

	if (found_num == k_undefined)
	{
		_cprintf("could not find list element for %d|%d %d|%d\n", r1, s1, r2, s2);
	}

	return found_num;
}

void COpponentModeling::Prw1326ChangeWeightOnList(int player_ndx, int old_weight, int new_weight)
{
	/*
	changes all hands with old_weight to new_weight
	*/
	int max_card = _prw1326->chair[player_ndx].limit;
	for (int z = 0; z < max_card; z++)
	{
		int r1 = _prw1326->chair[player_ndx].ranklo[z] % 13;
		int r2 = _prw1326->chair[player_ndx].rankhi[z] % 13;
		int s1 = _prw1326->chair[player_ndx].ranklo[z] - _prw1326->chair[player_ndx].ranklo[z] % 13;
		int s2 = _prw1326->chair[player_ndx].rankhi[z] - _prw1326->chair[player_ndx].rankhi[z] % 13;

		Prw1326WeightListElement(player_ndx, r1, r2, s1, s2, new_weight);
	}
}

/////////////////////////////////////////////////////    
// Preflop support functions   
/////////////////////////////////////////////////////
void COpponentModeling::Prw1326AddPocketPair(int player_ndx, int r1, int weight)
{
	/*
	adds pocket pair
	*/
	for (int p = 0; p < 3; p++)
	{
		for (int k = p + 1; k < 4; k++)
		{
			Prw1326AddListElement(player_ndx, r1, r1, k_prw1326_suit[p], k_prw1326_suit[k], weight);
		}
	}
}

void COpponentModeling::Prw1326AddOffSuit(int player_ndx, int r1, int r2, int weight)
{
	/*
	adds off suited hand
	*/
	for (int p = 0; p < 4; p++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (k != p)
				Prw1326AddListElement(player_ndx, r1, r2, k_prw1326_suit[p], k_prw1326_suit[k], weight);
		}
	}
}

void COpponentModeling::Prw1326AddSuit(int player_ndx, int r1, int r2, int weight)
{
	/*
	adds suited hand
	*/
	for (int k = 0; k < 4; k++)
	{
		Prw1326AddListElement(player_ndx, r1, r2, k_prw1326_suit[k], k_prw1326_suit[k], weight);
	}
}

void COpponentModeling::Prw1326GetPocketPair(int player_ndx, int r1)
{
	/*
	adds pocket pair
	*/
	for (int p = 0; p < 3; p++)
	{
		for (int k = p + 1; k < 4; k++)
		{
			int ndx = Prw1326GetListElement(player_ndx, r1, r1, k_prw1326_suit[p], k_prw1326_suit[k]);
			prw1326_preflop[player_ndx].insert(ndx);
		}
	}
}

void COpponentModeling::Prw1326GetOffSuit(int player_ndx, int r1, int r2)
{
	/*
	adds off suited hand
	*/
	for (int p = 0; p < 4; p++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (k != p)
			{
				int ndx = Prw1326GetListElement(player_ndx, r1, r2, k_prw1326_suit[p], k_prw1326_suit[k]);
				prw1326_preflop[player_ndx].insert(ndx);
			}
		}
	}
}

void COpponentModeling::Prw1326GetSuit(int player_ndx, int r1, int r2)
{
	/*
	adds suited hand
	*/
	for (int k = 0; k < 4; k++)
	{
		int ndx = Prw1326GetListElement(player_ndx, r1, r2, k_prw1326_suit[k], k_prw1326_suit[k]);
		prw1326_preflop[player_ndx].insert(ndx);
	}
}
