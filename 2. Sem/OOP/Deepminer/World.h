#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include "Bot.h"

using namespace std;

class World {

private:

	int worldArray[5][5][10];
	int sizeX;
	int sizeY;
	int sizeZ;

public:

	World();
	~World();

	void whichPlain();
	void printLayer(int k);
	void printWorld();

	void getMenu();
	void beginMenu();
	void printStats(Bot* B, int n);
	void errorMsg();


	Bot* chooseBot();
	Bot* chooseRobot();
	void startGame(Bot* B, Bot* Robot);
	void setPositionPlayer(Bot* B);
	void setPositionRobot(Bot* B);
	void chooseMovePlayer(Bot* B);
	void chooseMoveRobot(Bot* B);
};
