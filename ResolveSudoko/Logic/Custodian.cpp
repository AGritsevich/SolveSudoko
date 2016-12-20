
#include "stdafx.h"
#include "Custodian.h"


CCustodian::CCustodian(void)
{
	Create();
}

CCustodian::~CCustodian(void)
{
	Clean();
}

bool CCustodian::Create()
{
	m_pCellVal = NULL;
	m_currentLevel = 0;

	m_pCellVal = new int**[BackupLevels];

	if ( m_pCellVal != NULL )
	{
		m_pCellVal[m_currentLevel] = new int*[COLUMN];

		if ( m_pCellVal[m_currentLevel] != NULL )
		{
			for (int x = 0; x < COLUMN; x++)
			{
				m_pCellVal[m_currentLevel][x] = new int[ROW];
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}

	return true;
}

void CCustodian::Clean()
{
	if (  m_pCellVal != NULL )
	{
		for ( UINT level = 0; level < m_currentLevel; level++ )
		{
			for (int x = 0; x < COLUMN; x++)
			{
				if (m_pCellVal[level][x]) delete[] m_pCellVal[level][x];
				m_pCellVal[level][x] = NULL;
			}

			delete[] m_pCellVal[level];
		}
		delete[] m_pCellVal;
	}

	m_currentLevel = 0;
	m_pCellVal = NULL;//
}

void CCustodian::Set( int x, int y, int number )
{
	if ( m_pCellVal != NULL && m_pCellVal[m_currentLevel] && m_pCellVal[m_currentLevel][x] )
	{
		m_pCellVal[m_currentLevel][x][y] = number;
	}
}

void CCustodian::Set( PossibleNumbers number )
{
	if ( m_pCellVal != NULL && m_pCellVal[m_currentLevel] && m_pCellVal[m_currentLevel][number.x] )
	{
		m_pCellVal[m_currentLevel][number.x][number.y] = number.number;
	}
}

int CCustodian::Get( int x, int y )
{
	if ( m_pCellVal != NULL && m_pCellVal[m_currentLevel] && m_pCellVal[m_currentLevel][x] )
	{
		return m_pCellVal[m_currentLevel][x][y];
	}

	return -1;
}

bool CCustodian::CreateBackUp()
{
	if ( (m_currentLevel + 1) >= BackupLevels )
	{
			return false;
	}

	m_currentLevel++;

	m_pCellVal[m_currentLevel] = new int*[COLUMN];

	if ( m_pCellVal[m_currentLevel] != NULL )
	{
		for ( int x = 0; x < COLUMN; x++ )
		{
			m_pCellVal[m_currentLevel][x] = new int[ROW];

			if (m_pCellVal[m_currentLevel][x] == NULL )
			{
				m_currentLevel--;
				return false;
			}

			memcpy(m_pCellVal[m_currentLevel][x], m_pCellVal[m_currentLevel - 1][x], sizeof(int)*ROW);
		}
	}
	else
	{
		m_currentLevel--;
		return false;
	}

	return true;
}

bool CCustodian::Rollback()
{
	if (m_pCellVal == NULL && m_pCellVal[m_currentLevel] == NULL ) return false;

	for ( int x = 0; x < COLUMN; x++ )
	{
		if (m_pCellVal[m_currentLevel][x] != NULL)
		{
			delete [] m_pCellVal[m_currentLevel][x];
		}
	}

	if (m_pCellVal[m_currentLevel]) delete [] m_pCellVal[m_currentLevel];
	m_pCellVal[m_currentLevel] = NULL;
	m_currentLevel--;

	return true;
}

