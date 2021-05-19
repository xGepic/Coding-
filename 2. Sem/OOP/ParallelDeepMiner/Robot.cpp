#include "Robot.h"

Robot::Robot() {

	score = 0;
	zValue = 9;
	xRobotPos = 0;
	yRobotPos = 0;
}

Robot::~Robot() {


}

int Robot::getScore() {

	return this->score;
}

void Robot::addScore(int n) {

	cout << "+" << n << " Points!" << endl;
	score += n;
}

void Robot::addExtra(int n) {

	cout << "+" << n << " ExtraPoints!" << endl;
	score += n;
}

int Robot::getzValue() {

	return this->zValue;
}

int Robot::getxRobotPos() {

	return this->xRobotPos;
}

void Robot::setxRobotPos(int pos) {

	xRobotPos += pos;
}

int Robot::getyRobotPos() {

	return this->yRobotPos;
}
void Robot::setyRobotPos(int pos) {

	yRobotPos += pos;
}

BotOne::BotOne() {

	xRobotPos = 0;
	yRobotPos = 0;
}

BotOne::~BotOne() {


}

void BotOne::mine(vector<int> depth) {

	int value = 0;
	int counter = count(depth.begin(), depth.end(), 4);

	sort(depth.begin(), depth.end());
	depth.pop_back();
	value = depth.back();

	if (counter > 0) {

		addExtra(counter);
	}
	addScore(value);
}

BotTwo::BotTwo() {

	xRobotPos = 4;
	yRobotPos = 4;
}

BotTwo::~BotTwo() {


}

void BotTwo::mine(vector<int> depth) {

	int value = 0;
	int counter = count(depth.begin(), depth.end(), 4);

	sort(depth.begin(), depth.end());
	depth.pop_back();
	value = depth.back();

	if (counter > 0) {

		addExtra(counter);
	}
	addScore(value);
}