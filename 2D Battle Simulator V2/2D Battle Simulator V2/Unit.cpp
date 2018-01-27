#include "Unit.h"

//int Unit::_unitTeamNum;
int Unit::_unitTeamSize;
int Unit::_unitEnemySize;
string Unit::_unitTeamName;
string Unit::_unitEnemyName;

Unit::Unit(string name, char tile, int attack, int defence, int hitpoints)
:_tile(tile), _unitName(name), _attack(attack), _defence(defence), _hitpoints(hitpoints)
{}

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

void Unit::setTeamSize(int size)
{

	_unitTeamSize = size;
}

void Unit::setEnemySize(int size)
{

	_unitEnemySize = size;
}

void Unit::setTeamName(string name)
{
	_unitTeamName = name;
}

void Unit::setEnemyName(string name)
{
	_unitEnemyName = name;
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