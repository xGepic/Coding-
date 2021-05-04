#pragma once 

#include <iostream>
#include <stdlib.h>
#include <stdexcept>

using namespace std;

class Player {

public:

	Player();
	Player(std::string name);
	virtual ~Player();
	virtual bool attack(Player* opponent) = 0; //TODO
	virtual double beAttacked() = 0; //TODO
	void rest();
	int getPoints();
	int getAttack();
	int getDefense();
	std::string getName();
	bool operator >(Player* P);

protected:
	int points;
	int defensePoints;
	int attackPoints;
	int attackBonus;
	int stamina;
	std::string name;

private:

};

class PlayerA : public Player {

public:
	PlayerA(string n);
	bool attack(Player* opponent);
	double beAttacked();
};

class PlayerB : public Player {

private:
	bool confused;

public:
	PlayerB(string n);
	bool attack(Player* opponent);
	double beAttacked();
};
