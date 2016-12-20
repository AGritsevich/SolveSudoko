
#pragma once
#include "defines.h"
#include "Custodian.h"
#include "Checker.h"


class CSolver
{
private:
	DWORD m_levelFork;
	CCustodian *m_data;
	CChecker m_checker;
	ContainerCoordinate	m_lastFoundedNumber;
	
	std::set<int> m_possibleField[BackupLevels][ROW][COLUMN];
	std::vector<PossibleNumbers> m_possibleNumbers[BackupLevels];

private:
	CSolver(void);

	void InitPossibleFields();
	int CalcNumberInLitleSquare( int numSquare, int number);
	bool CheckNumberInHorizontalLine( const int y, int number);
	bool CheckNumberInVerticalLine( const int x, int number);

	void DelImpossibleNumbbersInSquare(int numSquare, const int number);
	void DelImpossiblleNumbersInHorizontalLines(int x, const int number);
	void DelImpossiblleNumbersInVerticalLines(int y, const int number);

	bool CreateListPossibleNumbers();
	
	bool SteptBackFork();
	bool CreateFork();
	
	void ClearPresentNumbers();
	void OnlyOnePossibleInSquare( int nSquare, const int number, int &countNumbers);
	void CopyDetectedNumbers(int &countNumbers);

public:
	CSolver(CCustodian *data);
	~CSolver(void);

	bool ResolveSudoko();
	void Clean();
};

