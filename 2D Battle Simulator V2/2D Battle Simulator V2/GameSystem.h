#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>
#include "Level.h"
#include "Unit.h"
#include "windows.h"

using namespace std;

class Gamesystem
{
public:
	Gamesystem();

	bool playGame();

	bool getWin(int teamNum);

private:
	Level _level;
};

