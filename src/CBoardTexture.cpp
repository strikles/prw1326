#include "CBoardTexture.h"

#include "CLogging.h"
#include "CSymbols.h"


void CBoardTexture::FlopTexture()
{
	// 3 StraightFlush		= 12
	// Trips				= 13
	// 3 Straight + 2 flush	= 12 * 3 = 36
	// 3 Straight rainbow	= 12
	// 3 Flush				= c(13, 3) - 12 = 274
	// Paired rainbow		= 13 * 12 = 156
	// Paired 2 - flush		= 13 * 12 = 156
	// Broadway + 2 flush	= [c(13, 3) - 12] * 3 = 822
	// HighCard Rainbow		= [c(13, 3) - 12] = 274

	//////////////////////////////////////////////
	// Flop Texture classification
	//////////////////////////////////////////////

	/*
	g_log->WriteLog(eSeverityDebug, eCatInfo, "suitbitscommon0:%u\n", g_symbols->get_suitbitscommon(0));
	g_log->WriteLog(eSeverityDebug, eCatInfo, "suitbitscommon1:%u\n", g_symbols->get_suitbitscommon(1));
	g_log->WriteLog(eSeverityDebug, eCatInfo, "suitbitscommon2:%u\n", g_symbols->get_suitbitscommon(2));
	g_log->WriteLog(eSeverityDebug, eCatInfo, "suitbitscommon3:%u\n", g_symbols->get_suitbitscommon(3));
	*/


#if 1

	////////////////////
	// TRIPS ON BOARD //
	////////////////////

	// 1. trips bingo (broadway)
	if (g_symbols->get_nrankedcommon() == 3 && g_symbols->get_ranklocommon() >= 10)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "trips bingo (broadway)\n");
	}
	// 2. trips bingo (low)
	else if (g_symbols->get_nrankedcommon() == 3 && g_symbols->get_rankhicommon() < 10)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "trips bingo (low)\n");
	}

	//////////////
	// MONOTONE //
	//////////////

	// 3. monotone (broadway royal straightflush draw)
	else if (g_symbols->get_nsuitedcommon() == 3 && g_symbols->get_ranklocommon() >= 10 && g_symbols->get_nstraightflushfillcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "monotone (broadway royal straightflush draw)\n");
	}
	// 4. monotone (broadway straightflush draw)
	else if (g_symbols->get_nsuitedcommon() == 3 && g_symbols->get_rankhicommon() >= 10 && g_symbols->get_nstraightflushfillcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "monotone (broadway straightflush draw)\n");
	}
	// 5. monotone (low straightflush draw)
	else if (g_symbols->get_nsuitedcommon() == 3 && g_symbols->get_rankhicommon() < 10 && g_symbols->get_nstraightflushfillcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "monotone (low straightflush draw)\n");
	}
	// 6. monotone (broadway flush draw)
	else if (g_symbols->get_nsuitedcommon() == 3 && g_symbols->get_rankhicommon() >= 10 && g_symbols->get_nstraightflushfillcommon() > 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "monotone (broadway flush draw)\n");
	}
	// 7. monotone (low flush draw)
	else if (g_symbols->get_nsuitedcommon() == 3 && g_symbols->get_rankhicommon() < 10 && g_symbols->get_nstraightflushfillcommon() > 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "monotone (low flush draw)\n");
	}

	////////////
	// PAIRED //
	////////////

	// 8. paired (broadway pair + broadway card & 2 suited)
	else if (g_symbols->get_nrankedcommon() == 2 && g_symbols->get_trankcommon() >= 10 && g_symbols->get_ranklocommon() >= 10 && g_symbols->get_nsuitedcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "paired (broadway pair + broadway card & 2 suited)\n");
	}
	// 9. paired (broadway pair + low card & 2 suited)
	else if (g_symbols->get_nrankedcommon() == 2 && g_symbols->get_trankcommon() >= 10 && g_symbols->get_ranklocommon() < 10 && g_symbols->get_nsuitedcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "paired (broadway pair + low card & 2 suited)\n");
	}
	// 10. paired (low pair + broadway card & 2 suited)
	else if (g_symbols->get_nrankedcommon() == 2 && g_symbols->get_trankcommon() < 10 && g_symbols->get_rankhicommon() >= 10 && g_symbols->get_nsuitedcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "paired (low pair + broadway card & 2 suited)\n");
	}
	// 11. paired (low pair + low card & 2 suited)
	else if (g_symbols->get_nrankedcommon() == 2 && g_symbols->get_trankcommon() < 10 && g_symbols->get_rankhicommon() < 10 && g_symbols->get_nsuitedcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "paired (low pair + low card & 2 suited)\n");
	}
	// 12. paired (broadway pair + broadway card)
	else if (g_symbols->get_nrankedcommon() == 2 && g_symbols->get_trankcommon() >= 10 && g_symbols->get_ranklocommon() >= 10)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "paired (broadway pair + broadway card)\n");
	}
	// 13. paired (broadway pair + low card)
	else if (g_symbols->get_nrankedcommon() == 2 && g_symbols->get_trankcommon() >= 10 && g_symbols->get_ranklocommon() < 10)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "paired (broadway pair + low card)\n");
	}
	// 14. paired (low pair + broadway card)
	else if (g_symbols->get_nrankedcommon() == 2 && g_symbols->get_trankcommon() < 10 && g_symbols->get_rankhicommon() >= 10)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "paired (low pair + broadway card)\n");
	}
	// 15. paired (low pair + low card)
	else if (g_symbols->get_nrankedcommon() == 2 && g_symbols->get_trankcommon() < 10 && g_symbols->get_rankhicommon() < 10)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "paired (low pair + low card)\n");
	}

	////////////////
	// 3 BROADWAY //
	////////////////

	// 16. 3 Broadway cards (2 suited + straight draw)
	else if (g_symbols->get_ranklocommon() >= 10 && g_symbols->get_nsuitedcommon() == 2 && g_symbols->get_nstraightfillcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "3 Broadway cards (2 suited + straight draw)\n");
	}
	// 17. 3 Broadway cards (rainbow + straigh draw)
	else if (g_symbols->get_ranklocommon() >= 10 && g_symbols->get_nstraightfillcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "3 Broadway cards (rainbow + straigh draw)\n");
	}

	////////////////
	// 2 BROADWAY //
	////////////////

	// 18. 2 Broadway cards (2 suited + straight draw)
	else if (bitcount(g_symbols->get_rankbitscommon() & 0xFC00) == 2 && g_symbols->get_nsuitedcommon() == 2 && g_symbols->get_nstraightfillcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "2 Broadway cards (2 suited + straight draw)\n");
	}
	// 19. 2 Broadway cards (rainbow + straigh draw)
	else if (bitcount(g_symbols->get_rankbitscommon() & 0xFC00) == 2 && g_symbols->get_nsuitedcommon() == 1 && g_symbols->get_nstraightfillcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "2 Broadway cards (rainbow + straigh draw)\n");
	}
	// 20. 2 Broadway cards (2 suited)
	else if (bitcount(g_symbols->get_rankbitscommon() & 0xFC00) == 2 && g_symbols->get_nsuitedcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "2 Broadway cards (2 suited)\n");
	}
	// 21. 2 Broadway cards (rainbow)
	else if (bitcount(g_symbols->get_rankbitscommon() & 0xFC00) == 2 && g_symbols->get_nsuitedcommon() == 1)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "2 Broadway cards (rainbow)\n");
	}

	////////////////
	// 1 BROADWAY //
	////////////////

	// 22. 1 Broadway cards (2 suited + straight draw)
	else if (bitcount(g_symbols->get_rankbitscommon() & 0xFC00) == 1 && g_symbols->get_nsuitedcommon() == 2 && g_symbols->get_nstraightfillcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "1 Broadway cards (2 suited + straight draw)\n");
	}
	// 23. 1 Broadway cards (rainbow + straigh draw)
	else if (bitcount(g_symbols->get_rankbitscommon() & 0xFC00) == 1 && g_symbols->get_nsuitedcommon() == 1 && g_symbols->get_nstraightfillcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "1 Broadway cards (rainbow + straigh draw)\n");
	}
	// 24. 1 Broadway cards (2 suited)
	else if (bitcount(g_symbols->get_rankbitscommon() & 0xFC00) == 1 && g_symbols->get_nsuitedcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "1 Broadway cards (2 suited)\n");
	}
	// 25. 1 Broadway cards (rainbow)
	else if (bitcount(g_symbols->get_rankbitscommon() & 0xFC00) == 1 && g_symbols->get_nsuitedcommon() == 1)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "1 Broadway cards (rainbow)\n");
	}


	////////////////
	// 0 BROADWAY //
	////////////////

	// 26. 0 Broadway cards (2 suited + straight draw)
	else if (bitcount(g_symbols->get_rankbitscommon() & 0xFC00) == 0 && g_symbols->get_nsuitedcommon() == 2 && g_symbols->get_nstraightfillcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "0 Broadway cards (2 suited + straight draw)\n");
	}
	// 27. 0 Broadway cards (rainbow + straigh draw)
	else if (bitcount(g_symbols->get_rankbitscommon() & 0xFC00) == 0 && g_symbols->get_nsuitedcommon() == 1 && g_symbols->get_nstraightfillcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "0 Broadway cards (rainbow + straigh draw)\n");
	}
	// 28. 0 Broadway cards (2 suited)
	else if (bitcount(g_symbols->get_rankbitscommon() & 0xFC00) == 0 && g_symbols->get_nsuitedcommon() == 2)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "0 Broadway cards (2 suited)\n");
	}
	// 29. 0 Broadway cards (rainbow)
	else if (bitcount(g_symbols->get_rankbitscommon() & 0xFC00) == 0 && g_symbols->get_nsuitedcommon() == 1)
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "0 Broadway cards (rainbow)\n");
	}

	// how did we get here
	else
	{
		g_log->WriteLog(eSeverityInfo, eCatBoardTexture, "how did we get here ???");
		system("pause");
	}

#endif
}

void CBoardTexture::TurnTexture()
{
}

void CBoardTexture::CalcTexture()
{
	switch (g_symbols->get_betround())
	{
		case eFlop:
			FlopTexture();
			break;
		case eTurn:
			TurnTexture();
			break;
		default:
			break;
	}
}
