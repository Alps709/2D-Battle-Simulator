#include "Gamesystem.h"


using namespace std;

Gamesystem::Gamesystem()
{
	_level.startGame();
	_level.initUnits();
}

bool Gamesystem::playGame()
{

	while (_level.getIsDone() == false)
	{

		//if you enter q it exits the loop and stops the program
		if (_level.chooseUnit())
		{
			return true;
		}
		_level.chooseYTeamSize();

		//if you enter q it exits the loop and stops the program
		if (_level.chooseEnemyUnit())
		{
			return true;
		}
		_level.chooseETeamSize();

		_level.generateTeams();
		_level.generateBattlefield();

		while (_level.getIsDone2() == false)
		{

			_level.yourTeamMove();

			_level.enemyTeamMove();

			_level.updateVisBattleField();
			system("cls");
			_level.printBattleStats();
			_level.print();
			_getch();

			//checks if a team won
			if (getWin(0) && getWin(1))
			{
				cout << "YOU TIED!" << endl;
				system("PAUSE");
			}
			else if (getWin(1))
			{
				cout << "YOU WON!" << endl;
				system("PAUSE");
			}
			else if (getWin(0))
			{
				cout << "YOU LOST!" << endl;
				system("PAUSE");
			}
		}
		_level.clearStuff();
	}
	return false;
}

bool Gamesystem::getWin(int teamNum)
{

	if (_level.getUnitTeamSize(teamNum) == 0)
	{
		_level.setIsDone2(true);
		return true;
	}
	return false;

}