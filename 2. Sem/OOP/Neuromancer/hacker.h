#pragma once
#include <iostream>
#include <algorithm>
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

	void changeLifePoints(int x);

	void attack(int whichZone);
};