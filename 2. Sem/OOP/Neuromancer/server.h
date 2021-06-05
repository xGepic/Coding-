#pragma once
#include <string>
#include <vector>

using namespace std;

struct zonen {

	string name;
	int defensePoints;
	int pressureValue;
};

class server {

private:
	int lifePoints;
	vector<zonen> zonenArray;

public:

	server();
	~server();

	int getLifePoints();
	int getZoneDefPoints(int whichZone);
	int getZonePressureVal(int whichZone);

	void lifePointsMinusOne();
	void pressureValSetZero(int whichZone);
	void give3DefPoints(int whichZone);
	void incPressureVal(int whichZone);
};
