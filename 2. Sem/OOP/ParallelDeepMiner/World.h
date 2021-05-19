#pragma once
#include <iostream>
#include "Robot.h"

using namespace std;

class World{

private:

	int worldArray[5][5][10];
	int sizeX;
	int sizeY;
	int sizeZ;

public:

	World();
	~World();
	void generate();
	void getMenu();
	void whichPlain();
	void printLayer(int k);
	void printWorld();
	void beginMenu();
	void printStats(Robot* B, int n);
	int getWorldScore();

	void setPositionRobot1(Robot* B);
	void setPositionRobot2(Robot* B);
	void chooseMoveRobot(Robot* B, int n);

	void startGame(Robot* Player1, Robot* Player2);
};