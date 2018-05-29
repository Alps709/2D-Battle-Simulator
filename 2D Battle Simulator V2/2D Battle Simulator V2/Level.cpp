#include <math.h>
#include <random>
#include <ctime>

#include "Level.h"
#include "GameSystem.h"

using namespace std;

int _battleFieldSQRT;
int _visBattleFieldSQRT;
int _battleFieldTrueSize;

vector <Unit> _unitTeam[2];
vector <vector <Unit*> > _battleField;

int setDefenderTeamNum(int attackingTeamNum);

int findClosestUnit(int unitYpos, int unitXpos, int teamNum);

bool canMove(int yPos, int xPos, int direction, int direction2);
bool chooseUnitByName(string &unitName, vector <Unit> &units);
bool chooseUnitByNumber(int &unitNumber, vector <Unit> &units);

int Level::getUnitTeamSize(int teamNum)
{
	int numAlive = 0;

	for (int i = 0; i < _unitTeam[teamNum].size(); i++)
	{
		if (_unitTeam[teamNum][i].getHealth() > 0)
		{
			numAlive++;
		}
	}
	return numAlive;
}

bool Level::chooseUnit()
{
	while (true)
	{
		string unitName;
		bool validName = false;

		system("cls");
		printf("Choose which unit you want on your team.\nThese are the units you have to choose from:\n\n");
		listUnits();

		cin >> unitName;
		Gamesystem::clearCin();

		//choose unit by full name
		if (!chooseUnitByName(unitName, units))
		{
			return false;
		}

		if (unitName != "")
		{
			int unitNumber;

			try
			{//this gets a string of a number eg("1") and converts it into an int (1)
				unitNumber = stoi(unitName.c_str());
			}
			catch (...) //catches any exception from invalid stoi() input
			{
				goto invalidinput;
			}

			if (!chooseUnitByNumber(unitNumber, units))
			{
				return false;
			}
		}
		else if (unitName == "q" || unitName == "Q")
		{
			return true;
		}
		else
		{
			invalidinput:
			cout << "\nYou inputted: " << unitName << "\n\n";
			cout << "That is an invalid unit name! Please try again.\n";
			system("PAUSE");
		}
	}
}

bool chooseUnitByName(string &unitName, vector <Unit> &units)
{
	//allows you to choose unit by entering the full unit name
	for (int i = 0; i < units.size() - 1; i++)
	{
		if (units[i].getName() == unitName)
		{
			Unit::setTeamName(unitName);
			Unit::setTeamTile(units[i].getTile());
			return false;
		}
	}
	return true;
}

bool chooseUnitByNumber(int &unitNumber, vector <Unit> &units)
{
	//allows you to choose unit by entering the unit number instead of typing the full unit name
	int j = 1;
	for (int i = 0; i < units.size() - 1; i++)
	{

		if (unitNumber == j)
		{
			Unit::setTeamName(units[j - 1].getName());
			Unit::setTeamTile(units[i].getTile());
			return false;
		}
		j++;
	}
	return true;
}

bool Level::chooseEnemyUnit()
{
	while (true)
	{
		string unitEnemyName;
		bool validName = false;

		system("cls");
		printf("Choose which unit you want on the enemy team.\nThese are the units you have to choose from:\n\n");
		listUnits();

		cin >> unitEnemyName;
		Gamesystem::clearCin();

		//allows you to choose unit by entering the full unit name
		for (int i = 0; i < units.size() - 1; i++)
		{

			if (units[i].getName() == unitEnemyName)
			{
				Unit::setEnemyName(unitEnemyName);
				Unit::setEnemyTile(units[i].getTile());
				return false;
			}
		}
		if (unitEnemyName != "")
		{
			int unitNumber;
			try
			{
				//this gets a string of a number eg("1") and converts it into an int (1)
				unitNumber = stoi(unitEnemyName.c_str());
			}
			catch (...) //catches any exception from invalid stoi() input
			{
				goto invalidinput;
			}
			//allows you to choose the unit by entering the unit number instead of typing the full unit name
			if (validName == false)
			{
				int j = 1;

				for (int i = 0; i < units.size(); i++)
				{
					if (unitNumber == j)
					{
						Unit::setEnemyName(units[j - 1].getName());
						Unit::setEnemyTile(units[i].getTile());
						return false;
					}
					j++;
				}
			}
		}
		if (unitEnemyName == "q" || unitEnemyName == "Q")
		{
			return true;
		}
		else
		{
			invalidinput:
			cout << "\nYou inputted: " << unitEnemyName << "\n\n";
			cout << "That is an invalid unit name! Please try again.\n";
			system("PAUSE");
		}
	}
}

void Level::listUnits()
{
	string name;
	int attack;
	int defence;
	int hitpoints;

	for (int i = 0; i < units.size() - 1; i++)
	{
		units[i].getStats(name, attack, defence, hitpoints);
		printf("%i. %s: Attack %i, Defence %i, Hitpoints %i.\n\n", i + 1, name.c_str(), attack, defence, hitpoints);
	}
}

void Level::chooseYTeamSize()
{
	system("cls");
	
	int size;

	printf("How many units do you want in your team?\n");
	cin >> size;
	Gamesystem::clearCin();
	Unit::setTeamSize(size);
}

void Level::chooseETeamSize()
{
	system("cls");

	int size;

	printf("How many units do you want in the enemy team?\n");
	cin >> size;
	Gamesystem::clearCin();

	Unit::setEnemySize(size);
	system("cls");
}

void Level::generateTeams()
{
	string yourUnitName = Unit::getTeamName();
	string enemyUnitName = Unit::getEnemyName();
	 
	//Your team gets generated and stored in the vector
	for (int i = 0; i <= units.size(); i++)
	{

		if (yourUnitName == units[i].getName())
		{
			for (int j = 0; j < Unit::getTeamSize(); j++)
			{
				_unitTeam[0].push_back(units[i]);
				_unitTeam[0][j].setTeamNum(0);
			}
			break;
		}
	}

	//Enemy team gets generated and stored in the vector
	for (int i = 0; i <= units.size(); i++)
	{
		if (enemyUnitName == units[i].getName())
		{
			for (int j = 0; j < Unit::getEnemySize(); j++)
			{
				_unitTeam[1].push_back(units[i]);
				_unitTeam[1][j].setTeamNum(1);
			}
			break;
		}
	}
}

void Level::generateBattlefield()
{
	float battleFieldSize = (Unit::getTeamSize() + Unit::getEnemySize()) * 1.5f;
	float battleFieldLength = sqrt(battleFieldSize);

	//used for both width and height of the battlefield
	_battleFieldSQRT = battleFieldLength + 1;
	_battleFieldTrueSize = _battleFieldSQRT * _battleFieldSQRT;

	//show size of variables for debugging purposes
	//cout << battleFieldSize     << endl
	//	   << battleFieldLength   << endl 
	//	   << _battleFieldSQRT	  << endl;

	//Initialise the battlefield
	//team0 is initialised first
	int team0Num = _unitTeam[0].size() - 1;
	for (int i = 0; i < _battleFieldSQRT; i++)
	{
		vector <Unit*> battleTile;
		for (int j = 0; j < _battleFieldSQRT; j++)
		{
			if (team0Num >= 0)
			{
				_unitTeam[0][team0Num].setUnitCoords(i, j);
				battleTile.push_back(&_unitTeam[0][team0Num]);
				team0Num--;
			}
			else
			{
				//if all of team 0's units have been assigned a place on the board, 
				//fill the rest with the placeholder unit.
				battleTile.push_back(&units[units.size() - 1]);
			}
		}
		_battleField.push_back(battleTile);
	}

	//team1 is initialised second
	//Team1 units are initialised from the bottom to the top
	int team1Num = _unitTeam[1].size() - 1;
	for (int a = _battleFieldSQRT - 1; a >= 0; a--)
	{
		//breaks out of loop if there are no more units to assign
		if (team1Num < 0)
		{
			break;
		}
		for (int b = _battleFieldSQRT - 1; b >= 0; b--)
		{
			if (team1Num >= 0)
			{
				_unitTeam[1][team1Num].setUnitCoords(a, b);
				_battleField[a][b] = &_unitTeam[1][team1Num];
				team1Num--;
			}
		}
	}
}

void Level::clearStuff()
{
	_battleFieldSQRT = 0;
	_visBattleFieldSQRT = 0;
	_battleFieldTrueSize = 0;
	_battleField.clear();
	_unitTeam[0].clear();
	_unitTeam[1].clear();
}

void Level::printBattleStats()
{
	int units0Alive = 0;
	int units1Alive = 0;

	//first loop to change between the teams
	for (int j = 0; j < 2; j++)
	{
		//second loop to go through the units
		for (int i = 0; i < _unitTeam[j].size(); i++)
		{
			//checks to make sure it's the right team, then only counts units with more than 0 hp
			if (j == 0 && _unitTeam[0][i].getHealth() > 0)
			{
				units0Alive++;
			}
			//checks to make sure it's the right team, then only counts units with more than 0 hp
			if (j == 1 && _unitTeam[1][i].getHealth() > 0)
			{
				units1Alive++;
			}
		}
	}
	//displays # of alive units
	cout << "Total units alive: " << units0Alive + units1Alive << ".\n"
		 << "Number of Team 1's units alive: " << units0Alive << ".\n"
		 << "Number of Team 2's units alive: " << units1Alive << ".\n";
}

void Level::printBattleField()
{
	//print the battleField

	//Print the top border
	for (int k = 0; k < _battleFieldSQRT + 2; k++)
	{
		cout << "#  ";
	}
	cout << endl;

	//Print the board
	for (int i = 0; i < _battleField.size(); i++)
	{
		//Prints the left side border
		cout << "#  ";
		//prints the battlefield
		for (int j = 0; j < _battleField.size(); j++)
		{
			cout << _battleField[i][j]->getTile() << "  ";
		}
		//prints the right side border
		cout << "#\n";
	}

	//Print the bottom border
	for (int m = 0; m < _battleFieldSQRT + 2; m++)
	{
		cout << "#  ";
	}
}

void Level::teamsMove()
{   
	//change between teams
	for (int teamNum = 0; teamNum < 2; teamNum++)
	{
		for (int unitNum = 0; unitNum < _unitTeam[teamNum].size(); unitNum++)
		{
			//the current unit
			Unit *unit = &_unitTeam[teamNum][unitNum];

			//if the unit is dead it gets erased from the vector
			if (unit->getHealth() == 0)
			{
				_unitTeam[teamNum].erase(_unitTeam[teamNum].begin() + unitNum);
				//since the array is one less,
				//we have to subtract from unitNum to not skip a unit
				unitNum--;
				continue;
			}

			int unitYPos, unitXPos;
			unit->getPos(unitYPos, unitXPos);

			//iterates through the enemy team and compares the position of each enemy unit
			//to the position of the currently selected unit, and finds the distance between them.
			//saves the shortest distance while iterating.
			unit->setClosestEnemyNum(findClosestUnit(unitYPos, unitXPos, (int)(!(bool)teamNum)));
			                                                          //           ^
			//Handles moving or battling of the selected unit         //lemme explain this shit 
			moveUnit(unit);                                           //I need the opposite teamNum,
		}                                                             //so I cast it to a bool 
	}                                                                 //and use ! to reverse the value
}                                                                     //then cast it back to an int
                                                                      //so it turns a 0 into a 1, and a 1 into a 0
int findClosestUnit(int unitYpos, int unitXpos, int teamNum)
{
	int enemyYPos, enemyXPos;
	int unitINumber = NULL;
	int shortestDistance = INT_MAX;

	//iterates through enemyteam
	for (int i = 0; i < _unitTeam[teamNum].size(); i++)
	{
		//checks if current enemy unit is alive
		if (_unitTeam[teamNum][i].getHealth() > 0)
		{
			_unitTeam[teamNum][i].getPos(enemyYPos, enemyXPos);
			//calculates manhattan distance to currently selected enemy
			int distance = abs(enemyYPos - unitYpos) + abs(enemyXPos - unitXpos);
			
			if (i == 0 || distance < shortestDistance)
			{	//sets new shortest distance
				shortestDistance = distance;
				unitINumber = i;
			}
		}
	}
	return unitINumber;
}

bool canMove(int yPos, int xPos, int direction, int direction2)
{
	//checks to see if new position is clear
	return (_battleField[yPos + direction][xPos + direction2]->getTile() == '.');
}

void Level::moveUnit(Unit *movingUnit)
{
	int closestEnemyNum = movingUnit->getClosestEnemyNum();
	int attackingTeamNum = movingUnit->getTeamNum();
	int defendingTeamNum = setDefenderTeamNum(attackingTeamNum);

	Unit *defendingUnit = &_unitTeam[defendingTeamNum][closestEnemyNum];

	int enemyYpos, enemyXpos, unitYpos, unitXpos;
	//gets the position of the moving unit, and the defending unit (which is the closest enemy unit).
	movingUnit->getPos(unitYpos, unitXpos);
	defendingUnit->getPos(enemyYpos, enemyXpos);

	int dy = enemyYpos - unitYpos;
	int dx = enemyXpos - unitXpos;
	int ady = abs(enemyYpos - unitYpos);
	int adx = abs(enemyXpos - unitXpos);
	int distance = ady + adx;

	if (distance == 1)
	{//BATTLERUUUUUUUUUUUU!
		unitsBattle(movingUnit, defendingUnit);
	}
	else if (ady >= adx && dy > 0 && canMove(unitYpos, unitXpos, 1, 0))
	{//move towards enemy along y axis
	 //move down
		movingUnit->setUnitCoords(unitYpos + 1, unitXpos);
		_battleField[unitYpos + 1][unitXpos] = movingUnit;
		_battleField[unitYpos][unitXpos] = &units[units.size() - 1];
	}
	else if (ady >= adx && dy < 0 && canMove(unitYpos, unitXpos, -1, 0))
	{//move up
		movingUnit->setUnitCoords(unitYpos - 1, unitXpos);
		_battleField[unitYpos - 1][unitXpos] = movingUnit;
		_battleField[unitYpos][unitXpos] = &units[units.size() - 1];
	}
	else if (adx > ady && dx > 0 && canMove(unitYpos, unitXpos, 0, 1))
	{//move towards enemy along x axis
	 //move right
		movingUnit->setUnitCoords(unitYpos, unitXpos + 1);
		_battleField[unitYpos][unitXpos + 1] = movingUnit;
		_battleField[unitYpos][unitXpos] = &units[units.size() - 1];
	}
	else if (adx > ady && dx < 0 && canMove(unitYpos, unitXpos, 0, -1))
	{//move left
		movingUnit->setUnitCoords(unitYpos, unitXpos - 1);
		_battleField[unitYpos][unitXpos - 1] = movingUnit;
		_battleField[unitYpos][unitXpos] = &units[units.size() - 1];
	}
}

int setDefenderTeamNum(int attackingTeamNum)
{
	//type casting a bool to an int (false = 0, true = 1)
	//so this sets the defending team the opposite number of the attacking team
	return int(attackingTeamNum == 0);
}

void Level::unitsBattle(Unit *attackingUnit, Unit *defendingUnit)
{
	//initializes random generator
	mt19937 randomGenerator(time(NULL)*time(NULL));
	uniform_int_distribution <int> unitAttackRoll(1, attackingUnit->getAttack());

	//applys damage to the defending unit based from random attack roll
	defendingUnit->takeDamage(unitAttackRoll(randomGenerator));

	//check if defending unit died
	if (defendingUnit->getHealth() == 0)
	{
		//Defending unit died
		int unitYpos, unitXpos;
		defendingUnit->getPos(unitYpos, unitXpos);
		_battleField[unitYpos][unitXpos] = &units[units.size() - 1];
	}
}
