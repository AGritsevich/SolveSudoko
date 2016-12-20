
#pragma once

#include "defines.h"


class CCustodian
{
	friend class Checker;
	friend class Solver;
private:
	DWORD m_currentLevel;
	int ***m_pCellVal;// first level for backups, 2-rd - X, 3-rd Y coordinates.

	
public:
	//int **m_pCellVal;

public:
	CCustodian(void);
	~CCustodian(void);

	void Set(PossibleNumbers number);
	void Set(int x, int y, int number);
	int Get(int x, int y);

	bool CreateBackUp();
	bool Rollback();
	void Clean();
	bool Create();
};

