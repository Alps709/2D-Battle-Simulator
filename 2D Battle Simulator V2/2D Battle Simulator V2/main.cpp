#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>

#include "Gamesystem.h"

using namespace std;


int main()
{
	bool isGameDone = false;

	while (isGameDone == false)
	{
		isGameDone = Gamesystem::playGame();
	}
	return 0;
}
