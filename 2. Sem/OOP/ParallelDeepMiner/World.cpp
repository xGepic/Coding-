#include "World.h"

World::World() {

	sizeX = 5;
	sizeY = 5;
	sizeZ = 10;

	generate();
}

World::~World() {

	delete this;
}

void World::generate() {

	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			for (int k = 0; k < sizeZ; k++) {

				worldArray[i][j][k] = rand() % 9 + 1;
			}
		}
	}
}

void World::getMenu() {

	cout << "--| ParallelDeepMiner 1.0 by Stefan Simanek |--" << endl << endl;
}

void World::beginMenu() {

	cout << "Let the Game begin!" << endl;
	cout << "___________________" << endl << endl;
	printWorld();
}

void World::printStats(Robot* B, int n) {

	if (n == 1) {

		cout << "[SCORE] Player 1:	" << B->getScore() << " Points" << endl;
	}
	else {

		cout << "[SCORE] Player 2:	" << B->getScore() << " Points" << endl;
	}
}

void World::whichPlain() {

	int k = 0;

	while (true) {

		cout << "Which Plain would your like to Print? ";
		cin >> k;
		cout << endl;

		if ((k < 0) || (k > 9)) {

			cout << "[ERROR] The World only has 10 Plains! (0-9)" << endl << endl << endl;
		}
		else {
			printLayer(k);
		}
	}
}

void World::printLayer(int k) {

	cout << endl << endl << "Here is Layer Number " << k << ":" << endl;

	for (int i = 0; i < sizeX; i++) {

		for (int j = 0; j < sizeY; j++) {

			if (worldArray[i][j][k] == 88) {

				cout << "X" << " ";
			}
			else if (worldArray[i][j][k] == 89) {

				cout << "Y" << " ";
			}
			else {

				cout << worldArray[i][j][k] << " ";
			}
		}
		cout << endl;
	}
}

void World::printWorld() {

	int n = 0;

	cout << endl << "Here is your World!" << endl << endl;

	while (n < 10) {

		cout << "Layer " << n << ": " << endl;
		for (int i = 0; i < sizeX; i++) {

			for (int j = 0; j < sizeY; j++) {

				cout << worldArray[i][j][n] << " ";
			}
			cout << endl;
		}
		cout << endl;
		n++;
	}
}

void World::setPositionRobot1(Robot* B) {

	worldArray[B->getxRobotPos()][B->getyRobotPos()][B->getzValue()] = 'X';
}

void World::setPositionRobot2(Robot* B) {

	worldArray[B->getxRobotPos()][B->getyRobotPos()][B->getzValue()] = 'Y';
}


void World::chooseMoveRobot(Robot* B, int n) {

	int temp = rand() % 4 + 1;
	vector<int> temp2;

	if ((B->getyRobotPos() + 1 > 4) || (worldArray[B->getxRobotPos()][B->getyRobotPos() + 1][B->getzValue()] == 88)) {

		temp = 2;
	}
	if ((B->getxRobotPos() + 1 > 4) || (worldArray[B->getxRobotPos()][B->getyRobotPos() + 1][B->getzValue()] == 88)) {

		temp = 1;
	}
	if ((B->getyRobotPos() - 1 < 0) || (worldArray[B->getxRobotPos()][B->getyRobotPos() + 1][B->getzValue()] == 88)) {

		temp = 4;
	}
	if ((B->getxRobotPos() - 1 < 0) || (worldArray[B->getxRobotPos()][B->getyRobotPos() + 1][B->getzValue()] == 88)) {

		temp = 3;
	}
	if (temp == 4) {

		for (int j = 9; j > 0; j--) {

			worldArray[B->getxRobotPos()][B->getyRobotPos()][j] = 0;
		}
		B->setyRobotPos(1);
		if (n == 1) {
			setPositionRobot1(B);
		}
		if (n == 2) {
			setPositionRobot2(B);
		}
		for (int i = 9; i > 0; i--) {

			temp2.push_back(worldArray[B->getxRobotPos()][B->getyRobotPos()][i]);
		}
		B->mine(temp2);
	}
	if (temp == 3) {

		for (int j = 9; j > 0; j--) {

			worldArray[B->getxRobotPos()][B->getyRobotPos()][j] = 0;
		}
		B->setxRobotPos(1);
		if (n == 1) {
			setPositionRobot1(B);
		}
		if (n == 2) {
			setPositionRobot2(B);
		}
		for (int i = 9; i > 0; i--) {

			temp2.push_back(worldArray[B->getxRobotPos()][B->getyRobotPos()][i]);
		}
		B->mine(temp2);
	}
	if (temp == 2) {

		for (int j = 9; j > 0; j--) {

			worldArray[B->getxRobotPos()][B->getyRobotPos()][j] = 0;
		}
		B->setyRobotPos(-1);
		if (n == 1) {
			setPositionRobot1(B);
		}
		if (n == 2) {
			setPositionRobot2(B);
		}
		for (int i = 9; i > 0; i--) {

			temp2.push_back(worldArray[B->getxRobotPos()][B->getyRobotPos()][i]);
		}
		B->mine(temp2);
	}
	if (temp == 1) {

		for (int j = 9; j > 0; j--) {

			worldArray[B->getxRobotPos()][B->getyRobotPos()][j] = 0;
		}
		B->setxRobotPos(-1);
		if (n == 1) {
			setPositionRobot1(B);
		}
		if (n == 2) {
			setPositionRobot2(B);
		}
		for (int i = 9; i > 0; i--) {

			temp2.push_back(worldArray[B->getxRobotPos()][B->getyRobotPos()][i]);
		}
		B->mine(temp2);
	}
}

void World::startGame(Robot* Player1, Robot* Player2) {

	setPositionRobot1(Player1);
	setPositionRobot2(Player2);

	int temp = getWorldScore();
	int worldScore = temp - 89;
	cout << "WorldScore: " << worldScore << endl;

	while (Player1->getScore() < worldScore / 2 && Player2->getScore() < worldScore / 2) {

		cout << endl;
		printStats(Player1, 1);
		printStats(Player2, 2);
		printLayer(9);
		cout << endl;
		chooseMoveRobot(Player1, 1);
		chooseMoveRobot(Player2, 2);
	}
	cout << endl << "Final Score Player1: " << Player1->getScore() << endl;
	cout << "Final Score Player2: " << Player2->getScore() << endl;
}

int World::getWorldScore() {

	int temp = 0;

	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			temp += worldArray[i][j][9];
		}
	}
	return temp;
}