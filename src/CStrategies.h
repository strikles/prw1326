#pragma once



class CBaseStrategy
{
public:

	CBaseStrategy();
	virtual ~CBaseStrategy();

public:

	virtual bool	PrerequisiteMet() = 0;
	virtual int		StrategyAction() = 0;
	virtual bool	ContinueStrategy() = 0;

	virtual void	StatsNewHandStarted() = 0;
};



//////////////////////
// AGGRESSION PLAYS //
//////////////////////

// We bet because we have a good but vulnerable hand
class CProtect : public CBaseStrategy
{
public:

	CProtect();

public:

	virtual bool	PrerequisiteMet();
	virtual int		StrategyAction();
	virtual bool	ContinueStrategy();

	virtual void	StatsNewHandStarted();
};

// We bet to force opponents to fold
class CIsolate : public CBaseStrategy
{
public:

	CIsolate();

public:

	virtual bool	PrerequisiteMet();
	virtual int		StrategyAction();
	virtual bool	ContinueStrategy();

	virtual void	StatsNewHandStarted();
};



/////////////////////
// DECEPTION PLAYS //
/////////////////////

// We have a monster and we don't want to scare opponents ;)
class CSlowPlay : public CBaseStrategy
{
public:

	CSlowPlay();

public:

	virtual bool	PrerequisiteMet();
	virtual int		StrategyAction();
	virtual bool	ContinueStrategy();

	virtual void	StatsNewHandStarted();
};

// We capitalize on monster
class CCheckRaise : public CBaseStrategy
{
public:

	CCheckRaise();

public:

	virtual bool	PrerequisiteMet();
	virtual int		StrategyAction();
	virtual bool	ContinueStrategy();

	virtual void	StatsNewHandStarted();
};



////////////////
// WEAK PLAYS //
////////////////

// We are preflop and check or pay min. amt to continue 
class CLimp : public CBaseStrategy
{
public:

	CLimp();

public:

	virtual bool	PrerequisiteMet();
	virtual int		StrategyAction();
	virtual bool	ContinueStrategy();

	virtual void	StatsNewHandStarted();
};

// We are postflop and check / pay min. amt in hopes of hitting something
class CFloat : public CBaseStrategy
{
public:

	CFloat();

public:

	virtual bool	PrerequisiteMet();
	virtual int		StrategyAction();
	virtual bool	ContinueStrategy();

	virtual void	StatsNewHandStarted();
};




////////////
// BLUFFS //
////////////

/////////////
// PreFlop //
/////////////

// We steal blinds preflop
class CStealBlinds : public CBaseStrategy
{
public:

	CStealBlinds();

public:

	virtual bool	PrerequisiteMet();
	virtual int		StrategyAction();
	virtual bool	ContinueStrategy();

	virtual void	StatsNewHandStarted();
};

// We protect our blinds preflop
class CDefendBlinds : public CBaseStrategy
{
public:

	CDefendBlinds();

public:

	virtual bool	PrerequisiteMet();
	virtual int		StrategyAction();
	virtual bool	ContinueStrategy();

	virtual void	StatsNewHandStarted();
};

//////////////
// PostFlop //
//////////////

// We continue betting to show strength
class CContinuationBet : public CBaseStrategy
{
public:

	CContinuationBet();

public:

	virtual bool	PrerequisiteMet();
	virtual int		StrategyAction();
	virtual bool	ContinueStrategy();

	virtual void	StatsNewHandStarted();
};

// We bet out of position to pretend we hit something
class CDonkBet : public CBaseStrategy
{
public:

	CDonkBet();

public:

	virtual bool	PrerequisiteMet();
	virtual int		StrategyAction();
	virtual bool	ContinueStrategy();

	virtual void	StatsNewHandStarted();
};


/////////////
// GENERIC //
/////////////

// We bet and have something (small pair, draw, etc...) on a dangerous board
class CSemiBluff : public CBaseStrategy
{
public:

	CSemiBluff();

public:

	virtual bool	PrerequisiteMet();
	virtual int		StrategyAction();
	virtual bool	ContinueStrategy();

	virtual void	StatsNewHandStarted();
};

// We bet and have nothing at all :P
class CBluff : public CBaseStrategy
{
public:

	CBluff();

public:

	virtual bool	PrerequisiteMet();
	virtual int		StrategyAction();
	virtual bool	ContinueStrategy();

	virtual void	StatsNewHandStarted();
};