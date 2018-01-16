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
				playAgain();
			}
			else if (getWin(1))
			{
				cout << "YOU WON!" << endl;
				playAgain();
			}
			else if (getWin(0))
			{
				cout << "YOU LOST!" << endl;
				playAgain();
			}
			
		}
		_level.clearStuff();
	}
	return true;
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

void Gamesystem::playAgain()
{
	cout << "Do you want to play again? (y/n)" << endl;

	string yesOrNo;
	
	cin >> yesOrNo;
	_level.clearCin();

	if (yesOrNo == "y" || yesOrNo == "Y")
	{
		_level.setIsDone2(true);
	}
	else if (yesOrNo == "n" || yesOrNo == "N")
	{
		_level.setIsDone(true);
	}
	else
	{
		cout << "You did not enter a valid character,\nplease enter 'y' or 'n'.";
	}
}
