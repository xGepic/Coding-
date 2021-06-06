#pragma once
#include <iostream>
#include <mutex>
#include "server.h"

using namespace std;

class hacker{

private:
	int lifePoints;
	int attackPoints;
	int score; 
	string name;
	mutex m;

public:
	hacker(string namee),
	~hacker();

	int getAttackPoints();
	int getLifePoints();
	int getScore();
	string getName();

	void changeScore(int x);
	void changeAttackPoints(int x);
	void changeLifePoints(int x);
	int rng(int x);

	void attack(server* zone, int whichZone);
};
