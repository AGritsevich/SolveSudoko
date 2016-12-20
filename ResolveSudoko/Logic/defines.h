
#pragma once

#include <vector>
#include <set>

#define  BackupLevels 5

const int ROW = 9;
const int COLUMN = ROW;
const int LitleSquare = 3;
const int PossibleLowNumber = 1;
const int PossibleHighNumber = 9;

typedef struct _ResultCheking
{
	int x;
	int y;
	bool result;

	_ResultCheking()
	{
		result = false;
		x =y = 0;
	}

}ResultCheking;

typedef struct  _ContainerCoordinate
{
	int x;
	int y;

	_ContainerCoordinate(){ x =-1; y = -1;}

	_ContainerCoordinate(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
}ContainerCoordinate;

typedef struct _PossibleNumbers
{
	int x;
	int y;
	int number;

	_PossibleNumbers()
	{
		x = y = number;
	}

	_PossibleNumbers(int _x, int _y, int _number)
	{
		x = _x;
		y = _y;
		number = _number;
	}

	_PossibleNumbers(_PossibleNumbers &obj)
	{
		x = obj.x;
		y = obj.y;
		number = obj.number;
	}

}PossibleNumbers;

typedef std::vector<ContainerCoordinate> Coordinate;