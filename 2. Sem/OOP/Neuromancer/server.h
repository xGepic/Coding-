#pragma once
#include <algorithm>
#include "hacker.h"

using namespace std;

class server{

private:
	int lifePoints;

public:
	server();
	virtual ~server();
	virtual void beAttacked() = 0;
};

class defenseZone1 : public server {

private:
	int defensePoints;
	int pressureValue;

public:
	defenseZone1();
	virtual ~defenseZone1();
	void beAttacked();
};

class defenseZone2 : public server {

private:
	int defensePoints;
	int pressureValue;

public:
	defenseZone2();
	virtual ~defenseZone2();
	void beAttacked();
};

class defenseZone3 : public server {

private:
	int defensePoints;
	int pressureValue;

public:
	defenseZone3();
	virtual ~defenseZone3();
	void beAttacked();
};

class defenseZone4 : public server {

private:
	int defensePoints;
	int pressureValue;

public:
	defenseZone4();
	virtual ~defenseZone4();	
	void beAttacked();
};

class defenseZone5 : public server {

private:
	int defensePoints;
	int pressureValue;

public:
	defenseZone5();
	virtual ~defenseZone5();
	void beAttacked();
};