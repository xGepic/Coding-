#pragma once
#include <iostream>
#include "server.h"

using namespace std;

class hacker{

private:
	int lifePoints;
	int attackPoints;
	int score;

public:
	hacker(),
	~hacker();

	int getAttackPoints();
	int getLifePoints();
	int getScore();

	void changeScore(int x);
	void changeAttackPoints(int x);
	void changeLifePoints(int x);

	void attack(server* zone);
};
