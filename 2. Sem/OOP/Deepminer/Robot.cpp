#include "World.h"

void World::setPositionRobot(Bot* B) {

	worldArray[B->getxRobotPos()][B->getyRobotPos()][B->getzValue()] = 'Y';
}

Bot* World::chooseRobot() {

	int temp = rand() % 3 + 1;

	if (temp == 1) {

		cout << "Bot chose BotOne!" << endl << endl << endl;
		return new BotOne();
	}
	if (temp == 2) {

		cout << "Bot chose BotTwo!" << endl << endl << endl;
		return new BotTwo();
	}
	else {

		cout << "Bot chose BotThree!" << endl << endl << endl;
		return new BotThree();
	}
}

void World::chooseMoveRobot(Bot* B) {

	int temp = rand() % 4 + 1;
	vector<int> temp2;

	if ((B->getyRobotPos() + 1 > 4) || (worldArray[B->getxRobotPos()][B->getyRobotPos() + 1][B->getzValue()] == 88)) {

		temp = 2;
	}
	if ((B->getxRobotPos() + 1 > 4) || (worldArray[B->getxRobotPos() + 1][B->getyRobotPos()][B->getzValue()] == 88)) {

		temp = 1;
	}
	if ((B->getyRobotPos() - 1 < 0) || (worldArray[B->getxRobotPos()][B->getyRobotPos() - 1][B->getzValue()] == 88)) {

		temp = 4;
	}
	if ((B->getxRobotPos() - 1 < 0) || (worldArray[B->getxRobotPos() - 1][B->getyRobotPos()][B->getzValue()] == 88)) {

		temp = 3;
	}
	if (temp == 4) {

		for (int j = 9; j > 0; j--) {

			worldArray[B->getxRobotPos()][B->getyRobotPos()][j] = 0;
		}
		B->setyRobotPos(1);
		setPositionRobot(B);
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
		setPositionRobot(B);
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
		setPositionRobot(B);
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
		setPositionRobot(B);
		for (int i = 9; i > 0; i--) {

			temp2.push_back(worldArray[B->getxRobotPos()][B->getyRobotPos()][i]);
		}
		B->mine(temp2);
	}
}
