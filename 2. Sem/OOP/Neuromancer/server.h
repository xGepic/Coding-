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
	string getZoneName(int whichZone);

	void lifePointsMinusOne();
	void pressureValSetZero(int whichZone);
	void giveDefPoints(int whichZone);
	void incPressureVal(int whichZone);
	void decZoneDefPoints(int whichZone);
	void incZoneDefPoints(int whichZone);
};
