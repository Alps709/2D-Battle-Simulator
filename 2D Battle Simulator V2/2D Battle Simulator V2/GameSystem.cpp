#include "Gamesystem.h"


using namespace std;

string _playerName;

bool isDone;
bool isDone2;

void initGame();
void startGame();
void playAgain();
void initUnits();

//Getters
bool getWin(int teamNum);
bool getIsDone() { return isDone; }
bool getIsDone2() { return isDone2; }


void initGame()
{
	startGame();
	initUnits();
}

bool Gamesystem::playGame()
{

	while (getIsDone() == false)
	{

		//if you enter q it exits the loop and stops the program
		if (Level::chooseUnit())
		{
			return true;
		}
		Level::chooseYTeamSize();

		//if you enter q it exits the loop and stops the program
		if (Level::chooseEnemyUnit())
		{
			return true;
		}
		Level::chooseETeamSize();

		Level::generateTeams();
		Level::generateBattlefield();

		while (getIsDone2() == false)
		{
			//The teams units all move
			Level::yourTeamMove();
			Level::enemyTeamMove();

			system("cls");
			Level::printBattleStats();
			Level::printBattleField();
			_getch();

			//checks if a team won
			if (getWin(0) && getWin(1))
			{
				cout << "YOU TIED!\n";
				playAgain();
			}
			else if (getWin(1))
			{
				cout << "YOU WON!\n";
				playAgain();
			}
			else if (getWin(0))
			{
				cout << "YOU LOST!\n";
				playAgain();
			}
			
		}
		Level::clearStuff();
	}
	return true;
}

void initUnits()
{
	Level::units.push_back(Unit("Soldier", 'S', 20, 5, 100));
	Level::units.push_back(Unit("Berserker", 'B', 35, 1, 100));
	Level::units.push_back(Unit("Guardian", 'G', 11, 10, 100));
	Level::units.push_back(Unit("Wizard", 'W', 40, 0, 100));
	Level::units.push_back(Unit("Goblin", 'G', 10, 0, 50));
	Level::units.push_back(Unit("Ogre", 'O', 35, 5, 150));
	Level::units.push_back(Unit("Dragon", 'D', 50, 10, 300));
	Level::units.push_back(Unit("NOUNIT", '.', 0, 0, 0));
}

void startGame()
{
	printf("Welcome to the 2D Combat Simulator!\n\nPlease enter your name: ");
	cin >> _playerName;
	Gamesystem::clearCin();
	system("cls");
	printf("Welcome to the 2D Combat Simulator %s!\n\n", _playerName.c_str());
	printf("This is where you will choose two teams that battle it out\nto see who is the strongest.\n"
		"You will be able to choose what type of unit each team will get\nand how many will be in each team."
		"\nWhich ever team defeats all of the other teams units will win.\n");
	system("PAUSE");
}

void playAgain()
{
	cout << "\nDo you want to play again? (y/n)\n";

	string yesOrNo;
	
	while (true)
	{
		cin >> yesOrNo;
		Gamesystem::clearCin();

		if (yesOrNo == "y" || yesOrNo == "Y")
		{
			isDone2 = true;
			return;
		}
		else if (yesOrNo == "n" || yesOrNo == "N")
		{
			isDone2 = false;
			return;
		}
		else
		{
			cout << "\nYou did not enter a valid character,\nplease enter 'y' or 'n':";
		}
	}
}

bool getWin(int teamNum)
{
	return (Level::getUnitTeamSize(teamNum) == 0);
}

void Gamesystem::clearCin()
{
	cin.ignore(64, '\n'); //These two functions clear the input 
	cin.clear();          //for when cin is next used, otherwise errors can occur
}
