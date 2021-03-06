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
	extern vector <Unit> units;

	bool chooseUnit(int teamNum);
	void chooseTeamsSize(int teamNum);
	void listUnits();

	void generateTeams();
	void generateBattlefield();
	void printBattleStats();
	void printBattleField();

	int getUnitTeamSize(int teamNum);

	void teamsMove();
	void moveUnit(Unit *unit);
	void unitsBattle(Unit *attackingUnit, Unit *defendingUnit);

	void clearStuff();
};

