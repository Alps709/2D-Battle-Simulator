#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>

#include "Gamesystem.h"

using namespace std;


int main()
{

	Gamesystem gameSystem;

	bool isGameDone = false;

	while (isGameDone == false)
	{
		isGameDone = gameSystem.playGame();
	}


	system("PAUSE");
	return 0;
}