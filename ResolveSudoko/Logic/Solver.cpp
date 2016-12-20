
#include "stdafx.h"
#include "Solver.h"
#include <afx.h>

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

CSolver::CSolver( CCustodian *data ) : m_levelFork(0), m_checker(data)
{
	m_data = data;

	InitPossibleFields();
}

CSolver::~CSolver( void )
{

}

void CSolver::InitPossibleFields()
{
	int full_mask[] = {1,2,3,4,5,6,7,8,9};

	for (int x = 0; x < COLUMN; x++ )
	{
		for (int y = 0; y < ROW; y++)
		{
			m_possibleField[m_levelFork][x][y].insert(full_mask, full_mask + ROW);;
		}
	}
}

void CSolver::Clean()
{
	for ( DWORD level = 0; level < m_levelFork; level++ )
	{
		for ( int x = 0; x < COLUMN; x++ )
		{
			for ( int y = 0; y < ROW; y++)
			{
				m_possibleField[level][x][y].clear();
			}
		}

		m_possibleNumbers[level].clear();
	}

	m_levelFork = 0;

	m_lastFoundedNumber = ContainerCoordinate();

	InitPossibleFields();

}

int CSolver::CalcNumberInLitleSquare( int numSquare, int number )
{
	int count = 0;
	m_lastFoundedNumber = ContainerCoordinate(-1, -1);

	int start_x = LitleSquare*(numSquare % LitleSquare);
	int start_y = LitleSquare*(int)(numSquare / LitleSquare);

	for (int x = start_x; x < start_x + LitleSquare; x++)
	{
		for (int y = start_y; y < start_y + LitleSquare; y++)
		{
			if ( m_data->Get(x, y) == number )
			{
				m_lastFoundedNumber = ContainerCoordinate(x, y);
				count++;
			}
		}
	}

	return count;
}

bool CSolver::CheckNumberInHorizontalLine( const int y, int number )
{
	bool retVal = false;
	m_lastFoundedNumber = ContainerCoordinate(-1, -1);

	for ( int x = 0; x < COLUMN; x++)
	{
		if ( m_data->Get(x, y) == number )
		{
			m_lastFoundedNumber = ContainerCoordinate(x, y);
			retVal = true;
			break;
		}
	}

	return retVal;
}

bool CSolver::CheckNumberInVerticalLine( const int x, int number )
{
	bool retVal = false;
	m_lastFoundedNumber = ContainerCoordinate(-1, -1);

	for ( int y = 0; y < ROW; y++)
	{
		if ( m_data->Get(x, y) == number )
		{
			m_lastFoundedNumber = ContainerCoordinate(x, y);
			retVal = true;
			break;
		}
	}

	return retVal;
}

void CSolver::DelImpossiblleNumbersInVerticalLines( int x, const int number )
{
	std::set<int>::iterator it;

	for ( int y = 0; y < COLUMN; y++)
	{
		if ( ( it = m_possibleField[m_levelFork][x][y].find(number)) != m_possibleField[m_levelFork][x][y].end() )
		{
			m_possibleField[m_levelFork][x][y].erase(it);
		}
	}
}

void CSolver::DelImpossiblleNumbersInHorizontalLines( int y, const int number )
{
	std::set<int>::iterator it;

	for ( int x = 0; x < COLUMN; x++)
	{
		if ( ( it = m_possibleField[m_levelFork][x][y].find(number)) != m_possibleField[m_levelFork][x][y].end() )
		{
			m_possibleField[m_levelFork][x][y].erase(it);
		}
	}
}

void CSolver::DelImpossibleNumbbersInSquare( int numSquare, const int number )
{
	int start_x = LitleSquare*(numSquare % LitleSquare);
	int start_y = LitleSquare*(int)(numSquare / LitleSquare);
	std::set<int>::iterator it;

	for (int x = start_x; x < start_x + LitleSquare; x++)
	{
		for (int y = start_y; y < start_y + LitleSquare; y++)
		{
			if ( ( it = m_possibleField[m_levelFork][x][y].find(number)) != m_possibleField[m_levelFork][x][y].end() )
			{
				m_possibleField[m_levelFork][x][y].erase(it);
			}
		}
	}
}

void CSolver::ClearPresentNumbers()
{
	std::set<int>::iterator it;

	for (int x = 0; x < COLUMN; x++)
	{
		for (int y = 0; y < ROW; y++)
		{
			if ( m_data->Get(x, y) != 0)
			{
				m_possibleField[m_levelFork][x][y].clear();
			}
		}
	}
}

void CSolver::OnlyOnePossibleInSquare( int nSquare, const int number, int &countNumbers )
{
	int start_x = LitleSquare*(nSquare % LitleSquare);
	int start_y = LitleSquare*(int)(nSquare / LitleSquare);

	bool possibleSquare[LitleSquare][LitleSquare] = 
	{
		{ true, true, true },
		{ true, true, true },
		{ true, true, true }
	};
	
	//check horizontal lines
	for ( int y = start_y; y < start_y + LitleSquare; y++ )
	{
		for ( int x = 0; x < COLUMN; x++ )
		{
			if ( x >= start_x && x < (start_x + LitleSquare) && m_data->Get(x, y) != 0 )
			{
				possibleSquare[x % LitleSquare][y % LitleSquare] = false;
			}

			if ( m_data->Get(x, y) == number)
			{
				possibleSquare[0][y % LitleSquare] = false;
				possibleSquare[1][y % LitleSquare] = false;
				possibleSquare[2][y % LitleSquare] = false;
				break;
			}
		}
	}

	//check vertical lines
	for ( int x = start_x; x < start_x + LitleSquare; x++ )
	{
		for ( int y = 0; y < ROW; y++ )
		{
			if ( y >= start_y && y < (start_y + LitleSquare) && m_data->Get(x, y) != 0 )
			{
				possibleSquare[x % LitleSquare][y % LitleSquare] = false;
			}

			if ( m_data->Get(x, y) == number)
			{
				possibleSquare[x % LitleSquare][0] = false;
				possibleSquare[x % LitleSquare][1] = false;
				possibleSquare[x % LitleSquare][2] = false;
				break;
			}
		}
	}

	int freeDeltaX = -1;
	int freeDeltaY = -1;

	for (int x = start_x; x < start_x + LitleSquare; x++)
	{
		for (int y = start_y; y < start_y + LitleSquare; y++)
		{
			if ( possibleSquare[x % LitleSquare][y % LitleSquare] == true)
			{
				if ( freeDeltaX == -1 )
				{
					freeDeltaX = x % LitleSquare;
					freeDeltaY = y % LitleSquare;
				}
				else
				{
					// more than 1 possible place
					return;
				}
			}
		}
	}

	if ( freeDeltaX == -1 ) return; // no variants

	m_data->Set(freeDeltaX + start_x, freeDeltaY + start_y, number);
	m_possibleField[m_levelFork][freeDeltaX + start_x][freeDeltaY + start_y].clear();
	countNumbers--;
}

void CSolver::CopyDetectedNumbers(int &countNumbers)
{
	std::set<int>::iterator it;

	for (int x = 0; x < COLUMN; x++)
	{
		for (int y = 0; y < ROW; y++)
		{
			if ( m_possibleField[m_levelFork][x][y].size() == 1)
			{
				if ( m_data->Get(x, y) != 0 )
				{
					assert(0);
				}

				it = m_possibleField[m_levelFork][x][y].begin();
				m_data->Set(x, y, *it);
				m_possibleField[m_levelFork][x][y].clear();

				countNumbers--;
			}
			else if (m_possibleField[m_levelFork][x][y].size() == 0 && m_data->Get(x, y) == 0 )
			{
				//dead fork
				countNumbers--;
				m_data->Set(x, y, PossibleLowNumber);
			}
		}
	}
}

bool CSolver::CreateListPossibleNumbers()
{
	bool retVal = false;

	if ( m_possibleNumbers[m_levelFork].size() != 0 ) return true;

	std::set<int>::iterator it;

	for ( UINT prob = 2; prob < PossibleHighNumber/*LitleSquare*/; prob++ )
	{
		for ( int x = 0; x < COLUMN; x++ )
		{
			for (int y = 0; y < ROW; y++)
			{
				if ( m_possibleField[m_levelFork][x][y].size() == prob )
				{
					it = m_possibleField[m_levelFork][x][y].begin();

					for ( UINT index = 0; index < m_possibleField[m_levelFork][x][y].size(); index++, it++ )
					{
						m_possibleNumbers[m_levelFork].push_back(PossibleNumbers(x, y, *it));
						retVal = true;
					}
				}
			}
		}
	}
	

	return retVal;
}

bool CSolver::SteptBackFork()
{
	if ( m_levelFork > 0 )
	{
		m_data->Rollback();

		for ( int x = 0; x < COLUMN; x++ )
		{
			for ( int y = 0; y < ROW; y++)
			{
				m_possibleField[m_levelFork][x][y].clear();
			}
		}

		m_levelFork--;

		if ( m_possibleNumbers[m_levelFork].size() == 0 ) SteptBackFork();

		return true;
	}

	return false;
}

bool CSolver::CreateFork()
{
	bool bhaveList = true;

	if ( m_data->CreateBackUp() && ( bhaveList = CreateListPossibleNumbers()) )
	{
		m_levelFork++;

		for ( int x = 0; x < COLUMN; x++ )
		{
			for ( int y = 0; y < ROW; y++)
			{
				m_possibleField[m_levelFork][x][y] = m_possibleField[m_levelFork - 1][x][y];
			}
		}

		PossibleNumbers chance = m_possibleNumbers[m_levelFork - 1].back();
		m_possibleNumbers[m_levelFork - 1].pop_back();

		m_data->Set(chance);
		m_possibleField[m_levelFork][chance.x][chance.y].clear();

	}
	else
	{
		if ( bhaveList == false) m_data->Rollback();
		return false;
	}

	return true;
}

bool CSolver::ResolveSudoko()
{
	int countNumbers = ROW*COLUMN;
	int previousCount = ROW*COLUMN;

	ClearPresentNumbers();

	do
	{
		previousCount = countNumbers;
		countNumbers = ROW*COLUMN;//refresh process

		for (int cur_number = PossibleLowNumber; cur_number <= PossibleHighNumber; cur_number++ )
		{
			for ( int nSquare = 0; nSquare < LitleSquare*LitleSquare; nSquare++ )
			{
				int count = 0;
				if ( ( count = CalcNumberInLitleSquare( nSquare, cur_number ) ) != 0)
				{
					int x = m_lastFoundedNumber.x;
					int y = m_lastFoundedNumber.y;

					countNumbers -= count;

					DelImpossibleNumbbersInSquare( nSquare, cur_number );
					DelImpossiblleNumbersInVerticalLines( x, cur_number );
					DelImpossiblleNumbersInHorizontalLines( y, cur_number );
				}
				else
				{
					OnlyOnePossibleInSquare(nSquare, cur_number, countNumbers);
				}
			}
		}

		CopyDetectedNumbers(countNumbers);

		if ( countNumbers == 0 )
		{
			if ( m_checker.CheckTable() == true )
			{
				break;
			}
			else
			{
				if ( SteptBackFork() == false ) return false;

				if ( CreateFork() == false ) SteptBackFork();

				countNumbers = ROW*COLUMN;//refresh process
			}
		}
		else
		{
			if ( previousCount == countNumbers )
			{
				if ( CreateFork() == false ) SteptBackFork();
			}
		}
	}
	
	while ( countNumbers );
	
	return true;
}


