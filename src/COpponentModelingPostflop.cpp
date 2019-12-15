#include "COpponentModeling.h"

#include "CLogging.h"
#include "CSymbols.h"
#include "util.h"

#include <vector>

void COpponentModeling::GiveVillainStraights(int player_ndx)
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
						prw1326_straights[player_ndx].insert(prw1326_ndx);
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
							prw1326_straights[player_ndx].insert(prw1326_ndx);
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

void COpponentModeling::GiveVillainFlushes(int player_ndx)
{
	// villain hit a flush - 2 cards required
	for (int s = 0; s < 4; s++)
	{
		if (bitcount(g_symbols->get_suitbitscommon(s)) == 3)
		{
			for (int rank1_ndx = 0; rank1_ndx < k_num_ranks; rank1_ndx++)
			{
				for (int rank2_ndx = rank1_ndx + 1; rank2_ndx < k_num_ranks; rank2_ndx++)
				{
					int prw1326_ndx = Prw1326GetListElement(player_ndx, rank1_ndx, rank2_ndx, k_prw1326_suit[s], k_prw1326_suit[s]);
					prw1326_flushes[player_ndx].insert(prw1326_ndx);
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
					prw1326_flushes[player_ndx].insert(prw1326_ndx);

					// 1 card used
					for (int suit = 0; suit < 4; suit++)
					{
						int prw1326_ndx = Prw1326GetListElement(player_ndx, rank1_ndx, rank2_ndx, k_prw1326_suit[suit], k_prw1326_suit[s]);
						prw1326_flushes[player_ndx].insert(prw1326_ndx);

						prw1326_ndx = Prw1326GetListElement(player_ndx, rank1_ndx, rank2_ndx, k_prw1326_suit[s], k_prw1326_suit[suit]);
						prw1326_flushes[player_ndx].insert(prw1326_ndx);
					}
				}
			}
		}
	}
}

void COpponentModeling::GiveVillainPairs(int player_ndx)
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
					prw1326_pairs[player_ndx].insert(prw1326_ndx);
					prw1326_ndx = Prw1326GetListElement(player_ndx, board_rank2, rank_ndx, k_prw1326_suit[p], k_prw1326_suit[k]);
					prw1326_pairs[player_ndx].insert(prw1326_ndx);
					prw1326_ndx = Prw1326GetListElement(player_ndx, board_rank3, rank_ndx, k_prw1326_suit[p], k_prw1326_suit[k]);
					prw1326_pairs[player_ndx].insert(prw1326_ndx);
				}

				if (g_symbols->get_betround() == eTurn)
				{
					int board_rank4 = g_symbols->get_$$cr3() - 2;
					if (board_rank4 == rank_ndx && p == k)
						continue;
					int prw1326_ndx = Prw1326GetListElement(player_ndx, board_rank4, rank_ndx, k_prw1326_suit[p], k_prw1326_suit[k]);
					prw1326_pairs[player_ndx].insert(prw1326_ndx);
				}

				if (g_symbols->get_betround() == eRiver)
				{
					int board_rank5 = g_symbols->get_$$cr4() - 2;
					if (board_rank5 == rank_ndx && p == k)
						continue;
					int prw1326_ndx = Prw1326GetListElement(player_ndx, board_rank5, rank_ndx, k_prw1326_suit[p], k_prw1326_suit[k]);
					prw1326_pairs[player_ndx].insert(prw1326_ndx);
				}
			}
		}
	}
}

void COpponentModeling::Prw1326PostflopFiltered(int player_ndx, int weight)
{
	// fill arrays
	GiveVillainStraights(player_ndx);
	GiveVillainPairs(player_ndx);
	GiveVillainFlushes(player_ndx);
	// merge
	std::set<int> villain_prw1326_postflop;
	villain_prw1326_postflop.insert(prw1326_straights[player_ndx].begin(), prw1326_straights[player_ndx].end());
	villain_prw1326_postflop.insert(prw1326_flushes[player_ndx].begin(), prw1326_flushes[player_ndx].end());
	villain_prw1326_postflop.insert(prw1326_pairs[player_ndx].begin(), prw1326_pairs[player_ndx].end());

	g_log->WriteLog(eSeverityInfo, eCatOpponentModeling, "pf:%d flushes:%d straights:%d pairs:%d\n", 
		prw1326_preflop[player_ndx].size(),
		prw1326_flushes[player_ndx].size(),
		prw1326_straights[player_ndx].size(),
		prw1326_pairs[player_ndx].size()
	);

	if (prw1326_preflop[player_ndx].size() == 0)
	{
		for (int ndx = 0; ndx < _prw1326->chair[player_ndx].limit; ndx++)
		{
			prw1326_preflop[player_ndx].insert(ndx);
		}
	}

	// filter from preflop cards
	for (auto ndx : prw1326_preflop[player_ndx])
	{
		auto ndx_is_in_postflop = villain_prw1326_postflop.find(ndx) != villain_prw1326_postflop.end();
		if(ndx_is_in_postflop)
			_prw1326->chair[player_ndx].weight[ndx] = weight;
		else
			_prw1326->chair[player_ndx].weight[ndx] = 128;

	}
}

void COpponentModeling::Prw1326PostflopNaive(int player_ndx, int weight)
{
	// fill arrays
	GiveVillainStraights(player_ndx);
	GiveVillainPairs(player_ndx);
	GiveVillainFlushes(player_ndx);
	// merge
	std::set<int> villain_prw1326;
	villain_prw1326.insert(prw1326_preflop[player_ndx].begin(), prw1326_preflop[player_ndx].end());
	villain_prw1326.insert(prw1326_straights[player_ndx].begin(), prw1326_straights[player_ndx].end());
	villain_prw1326.insert(prw1326_flushes[player_ndx].begin(), prw1326_flushes[player_ndx].end());
	villain_prw1326.insert(prw1326_pairs[player_ndx].begin(), prw1326_pairs[player_ndx].end());

	g_log->WriteLog(eSeverityInfo, eCatOpponentModeling, "pf:%d flushes:%d straights:%d pairs:%d\n",
		prw1326_preflop[player_ndx].size(),
		prw1326_flushes[player_ndx].size(),
		prw1326_straights[player_ndx].size(),
		prw1326_pairs[player_ndx].size()
	);

	for (auto ndx : villain_prw1326)
	{
		_prw1326->chair[player_ndx].weight[ndx] = weight;
	}
}

void COpponentModeling::Prw1326Postflop(int player_ndx, int weight)
{
	Prw1326PostflopFiltered(player_ndx, weight);
}
