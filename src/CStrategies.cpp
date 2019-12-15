#include "CStrategies.h"


CBaseStrategy::CBaseStrategy()
{
}


CBaseStrategy::~CBaseStrategy()
{
}



// CStealBlinds
CStealBlinds::CStealBlinds()
{
}

bool CStealBlinds::PrerequisiteMet()
{
	return false;
}

int CStealBlinds::StrategyAction()
{
	return 0;
}

bool CStealBlinds::ContinueStrategy()
{
	return false;
}

void CStealBlinds::StatsNewHandStarted()
{
}
