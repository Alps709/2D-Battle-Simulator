#include "Unit.h"

//these private static member variables need to be declared here or a linker error occurs (Error LNK2001)
int Unit::_unitTeamSize;
int Unit::_unitEnemySize;
string Unit::_unitTeamName;
string Unit::_unitEnemyName;
char Unit::_unitTeamTile;
char Unit::_unitEnemyTile;

Unit::Unit(string _name, char _tile, int _attack, int _defence, int _hitpoints, int _dodgeChance, int _parryChance, int _pReflectPercent)
	:_tile(_tile), _unitName(_name), _attack(_attack), _defence(_defence), _hitpoints(_hitpoints), m_dodgeChance(_dodgeChance), m_parryChance(_parryChance), m_pReflectPercent(_pReflectPercent)
{

}

void Unit::getStats(string &name, int &attack, int &defence, int &hitpoints)
{
	name = _unitName;
	attack = _attack;
	defence = _defence;
	hitpoints = _hitpoints;
}

void Unit::setUnitCoords(int ypos, int xpos)
{
	_xpos = xpos;
	_ypos = ypos;
}

void Unit::setTeamsSize(int teamNum, int size)
{
	if (!(bool)teamNum)
	{
		_unitTeamSize = size;
	}
	else
	{
		_unitEnemySize = size;
	}

}

void Unit::setTeamsTile(int teamNum, char tile)
{
	if (!(bool)teamNum)
	{
		_unitTeamTile = tile;
	}
	else
	{
		_unitEnemyTile = tile;
	}
}

void Unit::setTeamsName(int teamNum, string name)
{
	if (!(bool)teamNum)
	{
		_unitTeamName = name;
	}
	else
	{
		_unitEnemyName = name;
	}
}

void Unit::setTeamNum(int num)
{
	_unitTeamNum = num;
}

void Unit::setClosestEnemyNum(int number)
{
	_closestEnemyNum = number;
}

void Unit::getPos(int &ypos, int &xpos)
{
	ypos = _ypos;
	xpos = _xpos;
}

void Unit::takeDamage(int attackRoll)
{
	attackRoll -= _defence;
	//check if attack does damage
	if (attackRoll > 0)
	{
		_hitpoints -= attackRoll;
	}
	if (_hitpoints < 0)
	{
		_hitpoints = 0;
	}
}