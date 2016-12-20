
#pragma once
#include "defines.h"
#include "Custodian.h"

class CChecker
{
private:
	CCustodian *m_data;

private:
	CChecker(){};

	bool CheckLitleSquare(int numSquare);
	bool CheckHorizontalLine(int numLine);
	bool CheckVerticalLine(int numLine);

public:
	Coordinate m_erros;

public:
	CChecker(CCustodian *data);
	~CChecker();

	bool CheckTable();

};