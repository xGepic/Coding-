#include "Bot.h"

Bot::Bot() {

	score = 0;
	zValue = 9;
	xPlayerPos = 0;
	yPlayerPos = 0;
	xRobotPos = 4;
	yRobotPos = 4;
}

Bot::~Bot() {


}

int Bot::getScore() {

	return this->score;
}

int Bot::getzValue() {

	return this->zValue;
}

int Bot::getxPlayerPos() {

	return this->xPlayerPos;
}

int Bot::getyPlayerPos() {

	return this->yPlayerPos;
}

void Bot::setxPlayerPos(int pos) {

	xPlayerPos += pos;
}

void Bot::setyPlayerPos(int pos) {

	yPlayerPos += pos;
}

int Bot::getxRobotPos() {

	return this->xRobotPos;
}

void Bot::setxRobotPos(int pos) {

	xRobotPos += pos;
}

int Bot::getyRobotPos() {

	return this->yRobotPos;
}
void Bot::setyRobotPos(int pos) {

	yRobotPos += pos;
}

void Bot::addScore(int n) {

	cout << "+" << n << " Points!" << endl;
	score += n;
}
