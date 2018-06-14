#include <Windows.h>
#include "Gamesystem.h"
#include "Level.h"

using namespace std;

vector <Unit> Level::units; 

string _playerName;

bool isDone;
bool isDone2;

void getWin();
void initUnits();
void startGame();
void playAgain();

bool checkWin(int teamNum);

//MAIN GAME LOOP
bool Gamesystem::playGame()
{
	int yourTeamNum = 0;
	int enemyTeamNum = 1;
	initUnits();
	startGame();

	while (isDone == false)
	{
		//if you enter q it exits the loop and stops the program
		if (Level::chooseUnit(yourTeamNum))
		{
			return true;
		}
		Level::chooseTeamsSize(yourTeamNum);

		//if you enter q it exits the loop and stops the program
		if (Level::chooseUnit(enemyTeamNum))
		{
			return true;
		}
		Level::chooseTeamsSize(enemyTeamNum);

		Level::generateTeams();
		Level::generateBattlefield();

		//Initial print of the board
		Level::printBattleStats();
		Level::printBattleField();

		cout << "\nPress any key to start the battle!\n";
		_getch();

		isDone2 = false;
		while (isDone2 == false)
		{
			//The teams units all move
			Level::teamsMove();

			//Updates board
			system("cls");
			Level::printBattleStats();
			Level::printBattleField();

			//checks if a team won
			getWin();

			Sleep(500);
		}
		Level::clearStuff();
	}
	return true;
}

void Gamesystem::clearCin()
{
	cin.ignore(64, '\n');
	cin.clear();
}

void Gamesystem::invalidInput(string input)
{
	cout << "\nYou inputted: " << input << "\n\n";
	cout << "That is an invalid input! Please try again.\n";
	system("PAUSE");
}

void initUnits()
{                               //name       tile att def hp
	Level::units.push_back(Unit("Soldier",   'S', 20,  5, 100));
	Level::units.push_back(Unit("Berserker", 'B', 35,  1, 100));
	Level::units.push_back(Unit("Guardian",  'G', 11, 10, 100));
	Level::units.push_back(Unit("Wizard",    'W', 40,  0, 100));
	Level::units.push_back(Unit("Goblin",    'G', 10,  0,  50));
	Level::units.push_back(Unit("Ogre",      'O', 35,  5, 150));
	Level::units.push_back(Unit("Dragon",    'D', 50, 10, 300));
	Level::units.push_back(Unit("NOUNIT",    '.',  0,  0,   0));
}

void startGame()
{
	printf("Welcome to the 2D Combat Simulator!\n\nPlease enter your name: ");
	cin>> _playerName;

	system("cls");
	printf("Welcome to the 2D Combat Simulator %s!\n\n"
		   "This is where you will choose two teams that battle it out\nto see who is the strongest.\n"
		   "You will be able to choose what type of unit each team will get\nand how many will be in each team."
		   "\nWhich ever team defeats all of the other teams units will win.\n", _playerName.c_str());
	system("PAUSE");
}

void getWin()
{
	if (checkWin(0) && checkWin(1))
	{
		cout << "\nYOU TIED!\n";
		playAgain();
	}
	else if (checkWin(1))
	{
		cout << "\nYOU WON!\n";
		playAgain();
	}
	else if (checkWin(0))
	{
		cout << "\nYOU LOST!\n";
		playAgain();
	}
}

bool checkWin(int teamNum)
{
	return (Level::getUnitTeamSize(teamNum) == 0);
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
			isDone = true;
			isDone2 = true;
			return;
		}
		else
		{
			cout << "\nYou did not enter a valid character,\nplease enter 'y' or 'n':";
		}
	}
}
