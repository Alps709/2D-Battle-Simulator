#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <conio.h>

#include "Unit.h"


using namespace std;


namespace Level
{

	static vector <Unit> units;

	bool chooseUnit();
	bool chooseEnemyUnit();
	void chooseYTeamSize();
	void chooseETeamSize();
	void listUnits();

	void generateTeams();
	void generateBattlefield();
	void printBattleStats();
	void printBattleField();

	void yourTeamMove();
	void enemyTeamMove();

	int findClosestUnit(int unitYpos, int unitXpos);
	int findClosestEnemyUnit(int unitYpos, int unitXpos);

	bool canMove(int yPos, int xPos, int direction, int direction2);
	void moveUnit(Unit *unit);

	void unitsBattle(Unit *attackingUnit, Unit *defendingUnit);

	int setDefenderTeamNum(int attackingTeamNum);

	int getUnitTeamSize(int teamNum);

	void clearStuff();
};

