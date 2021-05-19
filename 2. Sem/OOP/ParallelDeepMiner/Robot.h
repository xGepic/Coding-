#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Robot{

private:

	int score;
	int zValue;


public:

	int xRobotPos;
	int yRobotPos;

	Robot();
	~Robot();

	int getScore();
	void addScore(int n);
	void addExtra(int n);
	int getzValue();

	int getxRobotPos();
	void setxRobotPos(int pos);
	int getyRobotPos();
	void setyRobotPos(int pos);

	virtual void mine(vector<int> depth) = 0;
};

class BotOne : public Robot {

private:


public:

	BotOne();
	virtual ~BotOne();

	void mine(vector<int> depth);
};

class BotTwo : public Robot {

private:


public:

	BotTwo();
	virtual ~BotTwo();

	void mine(vector<int> depth);
};