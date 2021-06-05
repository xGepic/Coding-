#pragma once
#include <string>

using namespace std;

class server{

private:
	int lifePoints;
	int defensePoints;
	int pressureValue;
	
public:
	string name;


	server();
	virtual ~server();

	int getDefensePoints();
	int getPressureValue();
	int getLifePoints();
	string getName();

	void changeLifePoints(int x);
	void changeDefensePoints(int x);
	void changePressureValue(int x);

	void setZero();

	virtual void beAttacked() = 0;
};

class defenseZone1 : public server {

private:


public:
	defenseZone1();
	virtual ~defenseZone1();
	void beAttacked();
};

class defenseZone2 : public server {

private:


public:
	defenseZone2();
	virtual ~defenseZone2();
	void beAttacked();
};

class defenseZone3 : public server {

private:


public:
	defenseZone3();
	virtual ~defenseZone3();
	void beAttacked();
};

class defenseZone4 : public server {

private:


public:
	defenseZone4();
	virtual ~defenseZone4();	
	void beAttacked();
};

class defenseZone5 : public server {

private:


public:
	defenseZone5();
	virtual ~defenseZone5();
	void beAttacked();
};
