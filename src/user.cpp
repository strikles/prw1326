//******************************************************************************
//
// This file is part of the OpenHoldem project
//    Source code:           https://github.com/OpenHoldem/openholdembot/
//    Forums:                http://www.maxinmontreal.com/forums/index.php
//    Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose: Very simple user-DLL as a starting-point
//
// Required OpenHoldem version: 12.1.6
//
//******************************************************************************

// Needs to be defined here, before #include "user.h"
// to generate proper export- and inport-definitions
#define USER_DLL

#include "user.h"
#include <conio.h>
#include <time.h>
#include <windows.h>

#include "OpenHoldemFunctions.h"

#include "CLogging.h"
#include "CSymbols.h"
#include "CExtractActions.h"
#include "CBoardTexture.h"
#include "COpponentModeling.h"
#include "CDecision.h"
#include "magicNumbers.h"

//******************************************************************************
//
// Place all your initalizations in the functions below
// DLLOnLoad() amd DLLOnUnLoad() get called by the DLL,
// the other functions get called by OpenHoldem
//
//******************************************************************************
CLogging* g_log = nullptr;
CSymbols* g_symbols = nullptr;
CExtractActions* g_extract_actions;
CBoardTexture* g_board_texture = nullptr;
COpponentModeling* g_opponent_modeling = nullptr;
CDecision* g_decision = nullptr;

bool is_busy = false;

void DLLOnLoad() 
{
}

void DLLOnUnLoad() 
{
	if (g_decision)
		delete g_decision;

	
	if (g_opponent_modeling)
		delete g_opponent_modeling;
	

	if (g_board_texture)
		delete g_board_texture;

	if (g_extract_actions)
		delete g_extract_actions;

	if (g_symbols)
		delete g_symbols;

	if (g_log)
		delete g_log;
}

void __stdcall DLLUpdateOnNewFormula() 
{
	if (g_decision)
		delete g_decision;

	
	if(g_opponent_modeling)
		delete g_opponent_modeling;
	

	if (g_board_texture)
		delete g_board_texture;

	if (g_extract_actions)
		delete g_extract_actions;

	if(g_symbols)
		delete g_symbols;

	if (g_log)
		delete g_log;

	g_log = new CLogging();
	g_log->WriteLogNoHeading(eSeverityInfo, eCatGeneral, ">>> Loading Formula.\n");
	g_symbols = new CSymbols();
	g_extract_actions = new CExtractActions();
	g_board_texture = new CBoardTexture();
	g_opponent_modeling = new COpponentModeling();
	g_decision = new CDecision();
}

void __stdcall DLLUpdateOnConnection() 
{
}

void __stdcall DLLUpdateOnHandreset() 
{
	g_extract_actions->ExtractActionsReset();
	g_opponent_modeling->HandReset();
}

void __stdcall DLLUpdateOnNewRound() 
{
}

void __stdcall DLLUpdateOnMyTurn() 
{
	is_busy = true;
	g_symbols->UpdateOHSymbols();
	g_board_texture->CalcTexture();
	g_extract_actions->ExtractActions();
	g_opponent_modeling->ModelOpponents();

	GetSymbol("cmd$recalc");
	g_decision->Decision();
	is_busy = false;
}

void __stdcall DLLUpdateOnHeartbeat() 
{
	//g_log->WriteLogNoHeading(eSeverityInfo, eCatGeneral, ">>> Heartbeat.\n");
}

//******************************************************************************
//
// ProcessQuery()
// Handling the lookup of dll$symbols
//
//******************************************************************************
DLL_IMPLEMENTS double __stdcall ProcessQuery(const char* pquery) 
{
	if (pquery == nullptr) 
	{
		return 0;
	}

	if (strncmp(pquery,"dll$test", 8) == 0) 
	{
		MessageBox(0, GetTableTitle(), TEXT("Table title"), 0);
		MessageBox(0, GetPlayerName(0), TEXT("Name of player 0"), 0);
		return GetSymbol("random");
	}

	if (strncmp(pquery, "dll$scrape", 10) == 0) 
	{
		char* scraped_result;
		int result_lenght;
		scraped_result = ScrapeTableMapRegion("p0balance", result_lenght);
		if (scraped_result != nullptr) 
		{
			// The TEXT() macro supports both ASCII and Unicode.
			// For the people who use Unicode but don't understand the "error".
			// http://www.maxinmontreal.com/forums/viewtopic.php?f=174&t=19999
			// http://stackoverflow.com/questions/15498070/what-does-t-stands-for-in-a-cstring
			MessageBox(0, scraped_result, TEXT("Scraped custom region"), 0);
			LocalFree(scraped_result);
		}
	}

	if (strncmp(pquery, "dll$iswait", 10) == 0)
	{
		return is_busy;
	}

	if (strncmp(pquery, "dll$decision", 12) == 0)
	{
		is_busy = true;
		g_symbols->UpdateOHSymbols();
		g_board_texture->CalcTexture();
		g_extract_actions->ExtractActions();
		g_opponent_modeling->ModelOpponents();

		GetSymbol("cmd$recalc");
		double decision = g_decision->Decision();
		is_busy = false;

		//system("pause");

		return decision;
	}

	return 0;
}

//******************************************************************************
//
// DLL entry point
//
//******************************************************************************

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) 
{
	switch (ul_reason_for_call)	
	{
		case DLL_PROCESS_ATTACH:
#ifdef _DEBUG
			//AllocConsole();
#endif _DEBUG
			InitializeOpenHoldemFunctionInterface();
			DLLOnLoad();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			DLLOnUnLoad();
#ifdef _DEBUG
			//FreeConsole();
#endif _DEBUG
			break;
	}

	return TRUE;
}
