#pragma once
#include <iostream>
#include <cstdlib>
#include <string>


using namespace std;

class Unit
{
public:
	Unit() {};
	Unit(string name, char tile, int attack, int defence, int hitpoints);


	void takeDamage(int attackRoll);

	//Getters (should all be const, unless static)
	string getName() const { return _unitName; };
	string getTeamName() const { return _unitTeamName; }
	string getEnemyName() const { return _unitEnemyName; }

	static int getTeamNum() { return _unitTeamNum; }
	static int getTeamSize() { return _unitTeamSize; };
	static int getEnemySize() { return _unitEnemySize; };
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
	static void setTeamSize(int size);
	static void setEnemySize(int size);
	static void setTeamName(string name);
	static void setEnemyName(string name);
	static void setTeamNum(int num);

	void setClosestEnemyNum(int number);
	void setUnitCoords(int ypos, int xpos);


private:

	static int _unitTeamNum;
	static int _unitTeamSize;
	static int _unitEnemySize;
	static string _unitTeamName;
	static string _unitEnemyName;

	string _unitName;
	char _tile;
	int _closestEnemyNum;
	int _attack;
	int _defence;
	int _hitpoints;

	//postion
	int _xpos;
	int _ypos;
};

