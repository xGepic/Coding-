#pragma once
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Bot {

private:
	int score;
	int zValue;
	int xPlayerPos;
	int yPlayerPos;
	int xRobotPos;
	int yRobotPos;

public:

	Bot();
	~Bot();

	int getScore();
	void addScore(int n);
	void addExtra(int n);
	int getzValue();

	int getxPlayerPos();
	void setxPlayerPos(int pos);
	int getyPlayerPos();
	void setyPlayerPos(int pos);

	int getxRobotPos();
	void setxRobotPos(int pos);
	int getyRobotPos();
	void setyRobotPos(int pos);

	virtual void mine(vector<int> depth) = 0;
};

class BotOne : public Bot {

private:


public:
	BotOne();
	virtual ~BotOne();

	void mine(vector<int> depth);
};

class BotTwo : public Bot {

private:


public:
	BotTwo();
	virtual ~BotTwo();

	void mine(vector<int> depth);
};

class BotThree : public Bot {

private:


public:
	BotThree();
	virtual ~BotThree();

	void mine(vector<int> depth);
};
