#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <conio.h>

#include "Unit.h"


using namespace std;


class Level
{
public:
	Level() {};

	void startGame();
	void initUnits();
	bool chooseUnit();
	bool chooseEnemyUnit();
	void chooseYTeamSize();
	void chooseETeamSize();
	void listUnits();

	void generateTeams();
	void generateBattlefield();
	void printBattleStats();
	void updateVisBattleField();
	void print();
	void printBattleField();

	void yourTeamMove();
	void enemyTeamMove();

	int findClosestUnit(int unitYpos, int unitXpos);
	int findClosestEnemyUnit(int unitYpos, int unitXpos);

	bool canMove(int yPos, int xPos, int direction, int direction2);
	void moveUnit(Unit *unit);

	void unitsBattle(Unit *attackingUnit, Unit *defendingUnit);

	int setDefenderTeamNum(int attackingTeamNum);

	bool getIsDone() { return _isDone; }
	bool getIsDone2() { return _isDone2; }

	void clearCin();

	int getUnitTeamSize(int teamNum);

	void setIsDone(bool isDone);
	void setIsDone2(bool isDone2);

	void clearStuff();


private:
	bool _isDone;
	bool _isDone2;
	string _name;
	int _battleFieldSQRT;
	int _visBattleFieldSQRT;
	int _battleFieldTrueSize;


	Unit _unit;
	vector <Unit> _units;
	vector <Unit> _unitTeam[2];

	vector <vector <char> > _visibleBattleField;
	vector <vector <Unit*> > _battleField;
};

