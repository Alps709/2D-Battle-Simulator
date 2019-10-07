#pragma once
#include <iostream>
#include <cstdlib>
#include <string>


using namespace std;

class Unit
{
public:
	Unit() {};
	Unit
	(
		string _name = "Default", 
		char _tile = 'd', 
		int _attack = 0, 
		int _defence = 0, 
		int _hitpoints = 0, 
		int _dodgeChance = 0, 
		int _parryChance = 0,
		int _pReflectPercent = 0
	);


	void takeDamage(int attackRoll);

	//Getters 
	string getName() { return _unitName; }
	static string getTeamName() { return _unitTeamName; }
	static string getEnemyName() { return _unitEnemyName; }
	static int getTeamSize() { return _unitTeamSize; }
	static int getEnemySize() { return _unitEnemySize; }
	static char getTeamTile() { return _unitTeamTile; }
	static char getEnemyTile() { return _unitEnemyTile; }

	int getTeamNum() const { return _unitTeamNum; }
	int getHealth() const { return _hitpoints; }
	int getAttack() const { return _attack; }
	int getDefence() const { return _defence; }
	int getXPos() const { return _xpos; }
	int getYPos() const { return _ypos; }
	int getClosestEnemyNum() const { return _closestEnemyNum; }

	char getTile() { return _tile; };
	void getPos(int &ypos, int &xpos);
	void getStats(string &name, int &attack, int &defence, int &hitpoints);


	//Setters
	void setTeamNum(int num);
	static void setTeamsSize(int teamNum, int size);
	static void setTeamsTile(int teamNum, char tile);
	static void setTeamsName(int teamNum, string name);

	void setClosestEnemyNum(int number);
	void setUnitCoords(int ypos, int xpos);


private:

	static int _unitTeamSize;
	static int _unitEnemySize;
	static char _unitTeamTile;
	static char _unitEnemyTile;
	static string _unitTeamName;
	static string _unitEnemyName;

	string _unitName;
	char _tile;
	int _unitTeamNum;
	int _closestEnemyNum;
	int _attack;
	int _defence;
	int m_dodgeChance; //Avoids damage completely
	int m_parryChance; //Reflects damage based on m_pReflectPercent
	int m_pReflectPercent;
	int _hitpoints;

	//postion
	int _xpos;
	int _ypos;
};

