#include "Level.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <conio.h>
#include <math.h>
#include <random>
#include <ctime>

#include "Unit.h"

using namespace std;

void Level::setIsDone2(bool isDone2)
{
	_isDone2 = isDone2;
}

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

void Level::startGame()
{

	printf("Welcome to the 2D Combat Simulator!\n\nPlease enter your name: ");
	getline(cin, _name);
	system("cls");
	printf("Welcome to the 2D Combat Simulator %s!\n\n", _name.c_str());
	printf("This is where you will choose two teams that battle it out\nto see who is the strongest.\n"
		"You will be able to choose what type of unit each team will get\nand how many will be in each team."
		"\nWhich ever team defeats all of the other teams units will win.\n");
	system("PAUSE");
}

void Level::initUnits()
{

	_units.push_back(Unit("Soldier", 'S', 20, 5, 100));
	_units.push_back(Unit("Berserker", 'B', 35, 1, 100));
	_units.push_back(Unit("Guardian", 'G', 11, 10, 100));
	_units.push_back(Unit("Wizard", 'W', 40, 0, 100));
	_units.push_back(Unit("Goblin", 'G', 10, 0, 50));
	_units.push_back(Unit("Ogre", 'O', 35, 5, 150));
	_units.push_back(Unit("Dragon", 'D', 50, 10, 300));
	_units.push_back(Unit("NOUNIT", '.', 0, 0, 0));

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

		getline(cin, unitName);


		//allows you to choose unit by entering the full unit name
		for (int i = 0; i < _units.size() - 1; i++)
		{

			if (_units[i].getName() == unitName)
			{
				_unit.setTeamName(unitName);
				return false;
			}
		}

		if (unitName != "")
		{
			//this gets a string of a number eg("1") and converts it into an int (1)
			int unitNumber = stoi(unitName.c_str());

			//allows you to choose unit by entering the unit number instead of typing the full unit name
			if (validName == false)
			{
				int j = 1;

				for (int i = 0; i < _units.size() - 1; i++)
				{

					if (unitNumber == j)
					{
						unitName = _units[j - 1].getName();
						_unit.setTeamName(unitName);
						return false;
					}
					j++;
				}
			}
		}
		if (unitName == "q" || unitName == "Q")
		{
			return true;
		}
		else if (validName == false)
		{
			cout << "\nYou inputted: " << unitName << "\n\n";
			cout << "That is an invalid unit name! Please try again.\n";
			system("PAUSE");
		}
	}
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


		getline(cin, unitEnemyName);

		//allows you to choose unit by entering the full unit name
		for (int i = 0; i < _units.size() - 1; i++)
		{

			if (_units[i].getName() == unitEnemyName)
			{
				_unit.setEnemyName(unitEnemyName);
				return false;
			}
		}


		if (unitEnemyName != "")
		{
			//this gets a string of a number eg("1") and converts it into an int (1)
			int unitNumber = stoi(unitEnemyName.c_str());

			//allows you to choose the unit by entering the unit number instead of typing the full unit name
			if (validName == false)
			{
				int j = 1;

				for (int i = 0; i < _units.size(); i++)
				{

					if (unitNumber == j)
					{
						unitEnemyName = _units[j - 1].getName();
						_unit.setEnemyName(unitEnemyName);
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

		cout << "\nYou inputted: " << unitEnemyName << "\n\n";
		cout << "That is an invalid unit name! Please try again.\n";
		system("PAUSE");

	}
}


void Level::listUnits()
{

	string name;
	int attack;
	int defence;
	int hitpoints;

	for (int i = 0; i < _units.size() - 1; i++)
	{
		_units[i].getStats(name, attack, defence, hitpoints);
		printf("%i. %s: Attack %i, Defence %i, Hitpoints %i.\n\n", i + 1, name.c_str(), attack, defence, hitpoints);
	}


}

void Level::chooseYTeamSize()
{

	system("cls");

	int size;

	printf("How many units do you want in your team?\n");
	cin >> size;
	cin.ignore(64, '\n'); //These two functions clear the input 
	cin.clear();          //for when cin is next used, otherwise errors can occur
	_unit.setTeamSize(size);
}

void Level::chooseETeamSize()
{

	system("cls");

	int size;

	printf("How many units do you want in the enemy team?\n");
	cin >> size;
	cin.ignore(64, '\n'); //These two functions clear the input 
	cin.clear();          //for when cin is next used, otherwise errors can occur
	_unit.setEnemySize(size);

	system("cls");
}

void Level::generateTeams()
{

	string yourUnitName = _unit.getTeamName();
	string enemyUnitName = _unit.getEnemyName();

	//Your team gets generated and stored in the vector
	for (int i = 0; i <= _units.size(); i++)
	{

		if (yourUnitName == _units[i].getName())
		{
			for (int j = 0; j < _unit.getTeamSize(); j++)
			{
				_unitTeam[0].push_back(_units[i]);
			}
			break;
		}
	}


	//Enemy team gets generated and stored in the vector
	for (int i = 0; i <= _units.size(); i++)
	{

		if (enemyUnitName == _units[i].getName())
		{
			for (int j = 0; j < _unit.getEnemySize(); j++)
			{
				_unitTeam[1].push_back(_units[i]);
			}
			break;
		}
	}
}

void Level::generateBattlefield()
{

	//used as placeholder Unit


	float battleFieldSize = (_unit.getTeamSize() + _unit.getEnemySize()) * 1.5f;
	float battleFieldLength = sqrt(battleFieldSize);

	//used for both width and height of the hidden battlefield
	_battleFieldSQRT = battleFieldLength + 1;

	_battleFieldTrueSize = _battleFieldSQRT * _battleFieldSQRT;

	//used for both width and height of the visible battlefield
	_visBattleFieldSQRT = _battleFieldSQRT + 2;


	//show size of variables for debugging purposes
	/*
	cout << battleFieldSize <<
	endl << battleFieldLength <<
	endl << _battleFieldSQRT <<
	endl << _visBattleFieldSQRT << endl;
	*/


	//Initialise the hidden battlefield

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
				_unitTeam[0][team0Num].setTeamNum(0);
				battleTile.push_back(move(&_unitTeam[0][team0Num]));
				team0Num--;
			}
			else
			{
				//if all of team 0's units have been assigned a place on the board, 
				//fill the rest with place holder units.
				battleTile.push_back(move(&_units[_units.size() - 1]));
			}
		}
		_battleField.push_back(move(battleTile));
	}

	//team1 is initialised second
	int team1Num = _unitTeam[1].size() - 1;

	//Team1 units are initialised from the bottom to the top
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
				_unitTeam[1][team1Num].setTeamNum(1);
				_battleField[a][b] = &_unitTeam[1][team1Num];
				team1Num--;
			}
		}
	}




	//initialise the visible battlefield
	for (int f = 0; f < _visBattleFieldSQRT; f++)
	{
		vector <char> visBattleTile;
		//If it's the first/last iteration of the loop, set the first/last wall
		if (f == 0 || f == _visBattleFieldSQRT - 1)
		{
			for (int c = 0; c < _visBattleFieldSQRT; c++)
			{
				visBattleTile.push_back('#');
			}

		}
		else
		{
			//set left side wall for this row of the battlefield
			visBattleTile.push_back('#');

			//set visible battle field to the tiles of the soldiers
			for (int g = 1; g < _visBattleFieldSQRT - 1; g++)
			{
				visBattleTile.push_back(move(_battleField[f - 1][g - 1]->getTile()));
			}
			//set right side wall for this row of the battlefield
			visBattleTile.push_back('#');
		}
		_visibleBattleField.push_back(move(visBattleTile));
	}


	system("PAUSE");
}

void Level::clearStuff()
{

	_battleField.clear();
	_visibleBattleField.clear();
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

void Level::print()
{

	//print the visibleBattlefield
	for (int i = 0; i < _visBattleFieldSQRT; i++)
	{
		for (int j = 0; j < _visBattleFieldSQRT; j++)
		{
			cout << _visibleBattleField[i][j] << "  ";
		}
		cout << endl;
	}
}

void Level::printBattleField()
{

	//print the battleField for debugging purposes
	for (int k = 0; k < _battleFieldSQRT + 2; k++)
	{
		cout << "#  ";
	}
	cout << endl;
	for (int i = 0; i < _battleField.size(); i++)
	{
		cout << "#  ";
		for (int j = 0; j < _battleField.size(); j++)
		{
			cout << _battleField[i][j]->getTile() << "  ";
		}
		cout << "#";
		cout << endl;
	}
	for (int m = 0; m < _battleFieldSQRT + 2; m++)
	{
		cout << "#  ";
	}

}

void Level::updateVisBattleField()
{

	for (int i = 0; i < _battleFieldSQRT - 1; i++)
	{
		for (int j = 0; j < _battleFieldSQRT - 1; j++)
		{
			_visibleBattleField[i + 1][j + 1] = _battleField[i][j]->getTile();
		}
	}

}

void Level::yourTeamMove()
{

	//num of units in the team that have been moved
	int teamUnitNum = 0;

	for (int i = 0; i < _battleFieldSQRT; i++)
	{
		for (int j = 0; j < _battleFieldSQRT; j++)
		{
			//makes sure it only does same # of checks as # of units in the team
			if (teamUnitNum < _unitTeam[0].size()
				//checks if the unit has the right tile
				&& _visibleBattleField[i + 1][j + 1] == _unitTeam[0][0].getTile()
				//checks if the unit is in the right team
				&& _battleField[i][j]->getTeamNum() == 0)
			{

				int unitYPos, unitXPos;

				_battleField[i][j]->getPos(unitYPos, unitXPos);

				//iterates through the enemy team and compares the position of each enemy unit
				//to the position of the currently selected unit, and finds the distance between them.
				//saves the shortest distance while iterating, until it is done.
				_battleField[i][j]->setClosestEnemyNum(findClosestUnit(unitYPos, unitXPos));

				moveUnit(_battleField[i][j]);

				//incremented to say we have moved another unit
				teamUnitNum++;
			}
		}
	}

}

void Level::enemyTeamMove()
{

	//num of units in the team that have been moved
	int enemyUnitNum = 0;

	for (int i = _battleFieldSQRT; i >= 0; i--)
	{
		for (int j = _battleFieldSQRT; j >= 0; j--)
		{
			//makes sure it only does same # of checks as # of units in the team
			if (enemyUnitNum < _unitTeam[1].size()
				//checks if the unit has the right tile
				&& _visibleBattleField[i + 1][j + 1] == _unitTeam[1][0].getTile()
				//checks if the unit is in the right team
				&& _battleField[i][j]->getTeamNum() == 1)
			{

				int unitYPos, unitXPos;

				_battleField[i][j]->getPos(unitYPos, unitXPos);

				//iterates through the enemy team and compares the position of each enemy unit
				//to the position of the currently selected unit, and finds the distance between them.
				//saves the shortest distance while iterating, until it is done.
				_battleField[i][j]->setClosestEnemyNum(findClosestEnemyUnit(unitYPos, unitXPos));

				moveUnit(_battleField[i][j]);

				//incremented to say we have moved another unit
				enemyUnitNum++;

			}
		}
	}

}


int Level::findClosestUnit(int unitYpos, int unitXpos)
{

	int enemyYPos, enemyXPos;
	int unitINumber = NULL;
	int shortestDistance = INT_MAX;

	//iterates through enemyteam
	for (int i = 0; i < _unitTeam[1].size(); i++)
	{
		//checks if current enemy unit is alive
		if (_unitTeam[1][i].getHealth() > 0)
		{

			_unitTeam[1][i].getPos(enemyYPos, enemyXPos);
			//calculates manhattan distance to currently selected enemy
			int distance = abs(enemyYPos - unitYpos) + abs(enemyXPos - unitXpos);

			if (i == 0 || distance < shortestDistance)
			{
				shortestDistance = distance;
				unitINumber = i;
			}
		}
	}

	return unitINumber;

}

int Level::findClosestEnemyUnit(int unitYpos, int unitXpos)
{

	int enemyYPos, enemyXPos;
	int unitINumber = NULL;
	int shortestDistance = INT_MAX;

	//iterates through enemyteam
	for (int i = 0; i < _unitTeam[0].size(); i++)
	{
		//checks if current enemy unit is alive
		if (_unitTeam[0][i].getHealth() > 0)
		{

			_unitTeam[0][i].getPos(enemyYPos, enemyXPos);
			//calculates manhattan distance to currently selected enemy
			int distance = abs(unitYpos - enemyYPos) + abs(unitXpos - enemyXPos);

			if (i == 0 || distance < shortestDistance)
			{
				shortestDistance = distance;
				unitINumber = i;
			}
		}
	}

	return unitINumber;

}

bool Level::canMove(int yPos, int xPos, int direction, int direction2)
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
		_battleField[unitYpos][unitXpos] = &_units[_units.size() - 1];
		_visibleBattleField[unitYpos + 2][unitXpos + 1] = movingUnit->getTile();
		_visibleBattleField[unitYpos + 1][unitXpos + 1] = '.';
	}
	else if (ady >= adx && dy < 0 && canMove(unitYpos, unitXpos, -1, 0))
	{	//move up
		movingUnit->setUnitCoords(unitYpos - 1, unitXpos);
		_battleField[unitYpos - 1][unitXpos] = movingUnit;
		_battleField[unitYpos][unitXpos] = &_units[_units.size() - 1];
		_visibleBattleField[unitYpos][unitXpos + 1] = movingUnit->getTile();
		_visibleBattleField[unitYpos + 1][unitXpos + 1] = '.';
	}
	else if (adx > ady && dx > 0 && canMove(unitYpos, unitXpos, 0, 1))
	{//move towards enemy along x axis

	 //move right
		movingUnit->setUnitCoords(unitYpos, unitXpos + 1);
		_battleField[unitYpos][unitXpos + 1] = movingUnit;
		_battleField[unitYpos][unitXpos] = &_units[_units.size() - 1];
		_visibleBattleField[unitYpos + 1][unitXpos + 2] = movingUnit->getTile();
		_visibleBattleField[unitYpos + 1][unitXpos + 1] = '.';
	}
	else if (adx > ady && dx < 0 && canMove(unitYpos, unitXpos, 0, -1))
	{  	//move left
		movingUnit->setUnitCoords(unitYpos, unitXpos - 1);
		_battleField[unitYpos][unitXpos - 1] = movingUnit;
		_battleField[unitYpos][unitXpos] = &_units[_units.size() - 1];
		_visibleBattleField[unitYpos + 1][unitXpos] = movingUnit->getTile();
		_visibleBattleField[unitYpos + 1][unitXpos + 1] = '.';
	}

}
int Level::setDefenderTeamNum(int attackingTeamNum)
{
	//type casting a bool to an int (false = 0, true = 1)
	//so this sets the defending team the opposite number of the attacking team
	return int(attackingTeamNum == 0);

}

void Level::unitsBattle(Unit *attackingUnit, Unit *defendingUnit)
{


	mt19937 randomGenerator(time(NULL));
	uniform_int_distribution <int> unitAttackRoll(1, attackingUnit->getAttack());

	defendingUnit->takeDamage(unitAttackRoll(randomGenerator));

	//check if defending unit died
	if (defendingUnit->getHealth() == 0)
	{
		//Defending unit died
		int unitYpos, unitXpos;
		defendingUnit->getPos(unitYpos, unitXpos);
		_battleField[unitYpos][unitXpos] = &_units[_units.size() - 1];
		_visibleBattleField[unitYpos + 1][unitXpos + 1] = '.';
	}

}
