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

	//Getters
	string getName() { return _unitName; };
	string getTeamName() { return _unitTeamName; }
	string getEnemyName() { return _unitEnemyName; }

	int getTeamNum() { return _unitTeamNum; }
	int getTeamSize() { return _unitTeamSize; };
	int getEnemySize() { return _unitEnemySize; };
	int getHealth() { return _hitpoints; }
	int getAttack() { return _attack; }
	int getDefence() { return _defence; }
	int getXPos() { return _xpos; }
	int getYPos() { return _ypos; }
	int getClosestEnemyNum() { return _closestEnemyNum; }

	char getTile() { return _tile; };

	void getPos(int &ypos, int &xpos);
	void getStats(string &name, int &attack, int &defence, int &hitpoints);


	//Setters
	void setTeamSize(int size);
	void setEnemySize(int size);
	void setTeamName(string name);
	void setEnemyName(string name);
	void setTeamNum(int num);
	void setClosestEnemyNum(int number);
	void setUnitCoords(int ypos, int xpos);


private:

	char _tile;
	string _unitName;
	int _unitTeamNum;
	int _unitTeamSize;
	string _unitTeamName;
	string _unitEnemyName;
	int _unitEnemySize;
	int _closestEnemyNum;
	int _attack;
	int _defence;
	int _hitpoints;


	//postion
	int _xpos;
	int _ypos;
};

