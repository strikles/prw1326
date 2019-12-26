#include "COpponentModeling.h"

#include "CLogging.h"
#include "CSymbols.h"
#include "util.h"

#include "inlines/eval.h"

#include <functional>
#include <map>

void COpponentModeling::GiveVillainStraights(int player_ndx, std::set<int> &straights)
{
	// villain hit a straight - 2 cards required
	if (g_symbols->get_nstraightfillcommon() <= 2)
	{
		unsigned int rankbitscommon = g_symbols->get_rankbitscommon();
		for (size_t i = 1; i < 10; i++)
		{
			unsigned int masked_value = rankbitscommon & (0x1F << i);
			if (bitcount(masked_value) == 3)
			{
				std::vector<int> cards;
				for (size_t j = i; j < i + 5; j++)
				{
					if (!(masked_value & (1 << j)))
					{
						if (j == 1)
							cards.push_back(12);
						else
							cards.push_back(j - 2);
					}
				}
				for (int p = 0; p < k_num_suits; p++)
				{
					for (int k = 0; k < k_num_suits; k++)
					{
						if (cards[0] == cards[1] && p == k)
							continue;

						int prw1326_ndx = Prw1326GetListElement(player_ndx, cards[0], cards[1], k_prw1326_suit[p], k_prw1326_suit[k]);
						straights.insert(prw1326_ndx);
					}
				}
				cards.empty();
			}
			// villain hit a straight - 1 cards required
			else if (bitcount(masked_value) == 4)
			{
				std::vector<int> cards;
				for (size_t j = i; j < i + 5; j++)
				{
					if (!(masked_value & (1 << j)))
					{
						if (j == 1)
							cards.push_back(12);
						else
							cards.push_back(j - 2);
					}
				}
				for (int rank_ndx = 0; rank_ndx < 13; rank_ndx++)
				{
					for (int p = 0; p < k_num_suits; p++)
					{
						for (int k = 0; k < k_num_suits; k++)
						{
							if (cards[0] == rank_ndx && p == k)
								continue;

							int prw1326_ndx = Prw1326GetListElement(player_ndx, cards[0], rank_ndx, k_prw1326_suit[p], k_prw1326_suit[k]);
							straights.insert(prw1326_ndx);
						}
					}
				}
				cards.empty();
			}
			// board is a straight and masked value is full so just continue
			else if (bitcount(masked_value) == 5)
			{
				continue;
			}
		}
	}
}

void COpponentModeling::GiveVillainFlushes(int player_ndx, std::set<int> &flushes)
{
	// villain hit a flush - 2 cards required
	for (int s = 0; s < k_num_suits; s++)
	{
		if (bitcount(g_symbols->get_suitbitscommon(s)) == 3)
		{
			for (int rank1_ndx = 0; rank1_ndx < k_num_ranks; rank1_ndx++)
			{
				for (int rank2_ndx = rank1_ndx + 1; rank2_ndx < k_num_ranks; rank2_ndx++)
				{
					int prw1326_ndx = Prw1326GetListElement(player_ndx, rank1_ndx, rank2_ndx, k_prw1326_suit[s], k_prw1326_suit[s]);
					flushes.insert(prw1326_ndx);
				}
			}
		}
		// villain hit a flush - 1 cards required
		if (bitcount(g_symbols->get_suitbitscommon(s)) >= 4)
		{
			for (int rank1_ndx = 0; rank1_ndx < k_num_ranks; rank1_ndx++)
			{
				for (int rank2_ndx = rank1_ndx + 1; rank2_ndx < k_num_ranks; rank2_ndx++)
				{
					// 2 cards used
					int prw1326_ndx = Prw1326GetListElement(player_ndx, rank1_ndx, rank2_ndx, k_prw1326_suit[s], k_prw1326_suit[s]);
					flushes.insert(prw1326_ndx);
					// 1 card used
					for (int suit = 0; suit < 4; suit++)
					{
						int prw1326_ndx = Prw1326GetListElement(player_ndx, rank1_ndx, rank2_ndx, k_prw1326_suit[suit], k_prw1326_suit[s]);
						flushes.insert(prw1326_ndx);
						prw1326_ndx = Prw1326GetListElement(player_ndx, rank1_ndx, rank2_ndx, k_prw1326_suit[s], k_prw1326_suit[suit]);
						flushes.insert(prw1326_ndx);
					}
				}
			}
		}
	}
}

void COpponentModeling::GiveVillainPairs(int player_ndx, std::set<int> &pairs)
{
	// villain hit a pair, two pair, trips or 4 of a kind
	int board_rank1 = g_symbols->get_$$cr0() - 2;
	int board_rank2 = g_symbols->get_$$cr1() - 2;
	int board_rank3 = g_symbols->get_$$cr2() - 2;

	for (int rank_ndx = 0; rank_ndx < k_num_ranks; rank_ndx++)
	{
		for (int p = 0; p < k_num_suits; p++)
		{
			for (int k = 0; k < k_num_suits; k++)
			{
				if (g_symbols->get_betround() == eFlop)
				{
					if (board_rank1 == rank_ndx && p == k)
						continue;
					if (board_rank2 == rank_ndx && p == k)
						continue;
					if (board_rank3 == rank_ndx && p == k)
						continue;

					int prw1326_ndx = Prw1326GetListElement(player_ndx, board_rank1, rank_ndx, k_prw1326_suit[p], k_prw1326_suit[k]);
					pairs.insert(prw1326_ndx);
					prw1326_ndx = Prw1326GetListElement(player_ndx, board_rank2, rank_ndx, k_prw1326_suit[p], k_prw1326_suit[k]);
					pairs.insert(prw1326_ndx);
					prw1326_ndx = Prw1326GetListElement(player_ndx, board_rank3, rank_ndx, k_prw1326_suit[p], k_prw1326_suit[k]);
					pairs.insert(prw1326_ndx);
				}
				if (g_symbols->get_betround() == eTurn)
				{
					int board_rank4 = g_symbols->get_$$cr3() - 2;
					if (board_rank4 == rank_ndx && p == k)
						continue;
					int prw1326_ndx = Prw1326GetListElement(player_ndx, board_rank4, rank_ndx, k_prw1326_suit[p], k_prw1326_suit[k]);
					pairs.insert(prw1326_ndx);
				}
				if (g_symbols->get_betround() == eRiver)
				{
					int board_rank5 = g_symbols->get_$$cr4() - 2;
					if (board_rank5 == rank_ndx && p == k)
						continue;
					int prw1326_ndx = Prw1326GetListElement(player_ndx, board_rank5, rank_ndx, k_prw1326_suit[p], k_prw1326_suit[k]);
					pairs.insert(prw1326_ndx);
				}
			}
		}
	}
}

void COpponentModeling::Prw1326NaivePostFlop(int player_ndx)
{
	std::set<int> prw1326_straights;
	std::set<int> prw1326_flushes;
	std::set<int> prw1326_pairs;
	// fill sets
	GiveVillainStraights(player_ndx, prw1326_straights);
	GiveVillainPairs(player_ndx, prw1326_pairs);
	GiveVillainFlushes(player_ndx, prw1326_flushes);
	// merge sets
	prw1326_postflop[player_ndx].insert(prw1326_straights.begin(), prw1326_straights.end());
	prw1326_postflop[player_ndx].insert(prw1326_flushes.begin(), prw1326_flushes.end());
	prw1326_postflop[player_ndx].insert(prw1326_pairs.begin(), prw1326_pairs.end());

	g_log->WriteLog(eSeverityInfo, eCatOpponentModeling, "pf:%d flushes:%d straights:%d pairs:%d\n",
		prw1326_preflop[player_ndx].size(),
		prw1326_flushes.size(),
		prw1326_straights.size(),
		prw1326_pairs.size()
	);
}

void COpponentModeling::Prw1326PostflopAND(int player_ndx, int weight)
{
	// fix preflop if required
	if (prw1326_preflop[player_ndx].size() == 0)
	{
		for (int ndx = 0; ndx < _prw1326->chair[player_ndx].limit; ndx++)
		{
			prw1326_preflop[player_ndx].insert(ndx);
		}
	}
	// fill postflop set
	Prw1326NaivePostFlop(player_ndx);
	// reset list
	Prw1326ChangeWeightOnList(player_ndx, 128);
	// logical AND of prw1326_preflop and prw1326_postflop
	for (auto ndx : prw1326_preflop[player_ndx])
	{
		auto ndx_is_in_postflop = prw1326_postflop[player_ndx].find(ndx) != prw1326_postflop[player_ndx].end();
		if(ndx_is_in_postflop)
			_prw1326->chair[player_ndx].weight[ndx] = weight;
		else
			_prw1326->chair[player_ndx].weight[ndx] = 128;
	}
}

void COpponentModeling::Prw1326PostflopOR(int player_ndx, int weight)
{
	// fix preflop if required
	if (prw1326_preflop[player_ndx].size() == 0)
	{
		for (int ndx = 0; ndx < _prw1326->chair[player_ndx].limit; ndx++)
		{
			prw1326_preflop[player_ndx].insert(ndx);
		}
	}
	// fill postflop set
	Prw1326NaivePostFlop(player_ndx);
	// reset
	Prw1326ChangeWeightOnList(player_ndx, 128);
	// logical OR of prw1326_preflop and prw1326_postflop
	for (auto ndx : prw1326_preflop[player_ndx])
	{
		_prw1326->chair[player_ndx].weight[ndx] = weight;
	}
	for (auto ndx : prw1326_postflop[player_ndx])
	{
		_prw1326->chair[player_ndx].weight[ndx] = weight;
	}
}

void COpponentModeling::Prw1326Postflop(int player_ndx, int weight)
{
	Prw1326PostflopOR(player_ndx, weight);
}

void COpponentModeling::Prw1326PostFlopRerank(int player_ndx)
{
	int betround = g_symbols->get_betround();
	CardMask common_cards = { 0 }, used_cards = { 0 }, player_cards = { 0 };
	std::map<unsigned int, unsigned int, std::greater<unsigned int> > ordered_postflop_1326_map;
	// player cards
	CardMask_SET(player_cards, g_symbols->get_$$pc0());
	CardMask_SET(player_cards, g_symbols->get_$$pc1());
	// common cards
	CardMask_SET(common_cards, g_symbols->get_$$cc0());
	CardMask_SET(common_cards, g_symbols->get_$$cc1());
	CardMask_SET(common_cards, g_symbols->get_$$cc2());
	if (eTurn <= g_symbols->get_betround())
		CardMask_SET(common_cards, g_symbols->get_$$cc3());
	if (eRiver == g_symbols->get_betround())
		CardMask_SET(common_cards, g_symbols->get_$$cc4());
	// merge masks
	CardMask_OR(used_cards, player_cards, common_cards);
	// iterate all 1326 combos
	for (int ndx = 0; ndx < 1326; ndx++)
	{
		CardMask rank_cards = { 0 };
		CardMask_SET(rank_cards, _prw1326->chair[player_ndx].rankhi[ndx]);
		CardMask_SET(rank_cards, _prw1326->chair[player_ndx].ranklo[ndx]);
		// check if combo is valid. if not set a pokerval of 0
		if (CardMask_ANY_SET(used_cards, rank_cards))
			ordered_postflop_1326_map.insert(std::make_pair(0, ndx));
		// calculate pokerval
		CardMask pokerval_mask = { 0 };
		CardMask_OR(pokerval_mask, common_cards, rank_cards);
		int num_cards = (eFlop == betround ? 5 : (eTurn == betround ? 6 : 7));
		unsigned int pokerval = Hand_EVAL_N(pokerval_mask, num_cards);
		// insert into map ordered by pokerval from greatest to smallest
		ordered_postflop_1326_map.insert(std::make_pair(pokerval, ndx));
	}
	// copy key-value pairs from the map to the vector in order to use the index
	std::map<unsigned int, unsigned int> ::iterator it;
	for (it = ordered_postflop_1326_map.begin(); it != ordered_postflop_1326_map.end(); it++)
	{
		prw1326_postflop_rerank[player_ndx].push_back(it->second);
	}
}

void COpponentModeling::Prw1326PostFlopTopList(int player_ndx, double play_pct)
{
	unsigned int include = (unsigned int)floor(play_pct * 1326) + 1;
	Prw1326PostFlopRerank(player_ndx);

	for (size_t ndx = 0; ndx < include; ndx++)
	{
		prw1326_postflop[player_ndx].insert(prw1326_postflop_rerank[player_ndx].at(ndx));
	}
}

void COpponentModeling::Prw1326PostFlopMiddleList(int player_ndx, double play_pct, double exclude_pct)
{
	unsigned int include = (unsigned int)floor(play_pct * 1326) + 1;
	unsigned int exclude = (unsigned int)floor(exclude_pct * 1326);
	assert(include > exclude);

	Prw1326PostFlopRerank(player_ndx);

	for (size_t ndx = exclude; ndx < include; ndx++)
	{
		prw1326_postflop[player_ndx].insert(prw1326_postflop_rerank[player_ndx].at(ndx));
	}
}

void COpponentModeling::Prw1326PostFlopBottomList(int player_ndx, double exclude_pct)
{
	unsigned int exclude = (unsigned int)floor(exclude_pct * 1326);
	Prw1326PostFlopRerank(player_ndx);

	for (size_t ndx = exclude; ndx < _prw1326->chair[player_ndx].limit; ndx++)
	{
		prw1326_postflop[player_ndx].insert(prw1326_postflop_rerank[player_ndx].at(ndx));
	}
}
