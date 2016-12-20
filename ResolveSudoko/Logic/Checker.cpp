
// ResolveSudoko.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Checker.h"


CChecker::CChecker(CCustodian *data)
{
	m_data = data;
}

CChecker::~CChecker()
{
	
}

//////////////////////////////////////////
//     0  1  2   3  4  5   6  7  8
//  0  a  b  c   d  e  f   g  k  l
//  1  d (0) f   g (1) l   a (2) c
//  2  g  k  l   a  b  c   d  e  f
//
//  3  b  c  a   e  f  d   f  d  e
//  4  e (3) d   k (4) g   l (5) k
//  5  k  l  g   b  c  a   c  a  b
//
//  6  c  a  b   a  b  c   b  c  a
//  7  f (6) e   d (7) f   e (8) d
//  8  l  g  k   g  k  l   k  l  g
///////////////////////////////////////////

bool CChecker::CheckLitleSquare( int numSquare )
{
	bool retVal = true;

	int start_x = LitleSquare*(numSquare % LitleSquare);
	int start_y = LitleSquare*(int)(numSquare / LitleSquare);

	ResultCheking numbers[LitleSquare*LitleSquare];

	for (int x = start_x; x < start_x + LitleSquare; x++)
	{
		for (int y = start_y; y < start_y + LitleSquare; y++)
		{
			int cur_number = m_data->Get(x, y) - 1;
			if ( cur_number >= 0 && numbers[cur_number].result == false && numbers[cur_number].x != -1)
			{
				numbers[cur_number].x = x;
				numbers[cur_number].y = y;
				numbers[cur_number].result = true;
			}
			else
			{
				m_erros.push_back(ContainerCoordinate(numbers[cur_number].x, numbers[cur_number].y ));
				m_erros.push_back(ContainerCoordinate(x, y));
				numbers[cur_number].x = numbers[cur_number].y = -1;
				numbers[cur_number].result = false;
			}
		}
	}

	for ( int index = 0; index < LitleSquare*LitleSquare; index++ )
	{
		retVal &= numbers[index].result;
	}

	return retVal;
}

bool CChecker::CheckHorizontalLine( int numLine )
{
	bool retVal = true;

	int y = numLine;
	ResultCheking numbers[LitleSquare*LitleSquare];

	for (int x = 0; x < COLUMN; x++)
	{
		int cur_number = m_data->Get(x, y) - 1;

		if ( cur_number >= 0 && numbers[cur_number].result == false && numbers[cur_number].x != -1)
		{
			numbers[cur_number].x = x;
			numbers[cur_number].y = y;
			numbers[cur_number].result = true;
		}
		else
		{
			m_erros.push_back(ContainerCoordinate(numbers[cur_number].x, numbers[cur_number].y ));
			m_erros.push_back(ContainerCoordinate(x, y));
			numbers[cur_number].x = numbers[cur_number].y = -1;
			numbers[cur_number].result = false;
		}
	}

	for ( int index = 0; index < LitleSquare*LitleSquare; index++ )
	{
		retVal &= numbers[index].result;
	}

	return retVal;
}

bool CChecker::CheckVerticalLine( int numLine )
{
	bool retVal = true;

	int x = numLine;
	ResultCheking numbers[LitleSquare*LitleSquare];

	for (int y = 0; y < ROW; y++)
	{
		int cur_number = m_data->Get(x, y) - 1;

		if ( cur_number >= 0 && numbers[cur_number].result == false && numbers[cur_number].x != -1)
		{
			numbers[cur_number].x = x;
			numbers[cur_number].y = y;
			numbers[cur_number].result = true;
		}
		else
		{
			m_erros.push_back(ContainerCoordinate(numbers[cur_number].x, numbers[cur_number].y ));
			m_erros.push_back(ContainerCoordinate(x, y));
			numbers[cur_number].x = numbers[cur_number].y = -1;
			numbers[cur_number].result = false;
		}
	}

	for ( int index = 0; index < LitleSquare*LitleSquare; index++ )
	{
		retVal &= numbers[index].result;
	}

	return retVal;
}

bool CChecker::CheckTable()
{
	bool retVal = true;

	//check squares
	for (int num = 0; num < LitleSquare*LitleSquare; num++)
	{
		retVal &= CheckLitleSquare(num);
	}

	if (retVal == false ) return retVal;

	//check Horizontal lines
	for (int line = 0; line < ROW; line++)
	{
		retVal &= CheckHorizontalLine(line);
	}

	if (retVal == false ) return retVal;

	//check Vertical line
	for (int line = 0; line < COLUMN; line++ )
	{
		retVal &= CheckVerticalLine(line);
	}

	return retVal;
}

