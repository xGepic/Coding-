#include "hacker.h"


hacker::hacker() {

	lifePoints = 1000;
	attackPoints = 30;
	score = 0;
}

hacker::~hacker() {


}

int hacker::getAttackPoints() {

	return this->attackPoints;
}

int hacker::getLifePoints() {

	return this->lifePoints;
}

int hacker::getScore() {

	return this->score;
}

void hacker::changeScore(int x) {

	score += x;
}

void hacker::changeLifePoints(int x) {

	lifePoints += x;
}

void hacker::changeAttackPoints(int x) {

	attackPoints += x;
}

void hacker::attack(server* zone, int whichZone) {

	int fail = rand() % 100;

	cout << "Zone " << whichZone << " is attacked!" << endl;

	if (fail == 42) {

		changeLifePoints(-5);
		cout << "1 % Chance - Attack Failed" << endl;
		return;
	}

	while (true) {

		if ((this->getAttackPoints() + zone->getZonePressureVal(whichZone)) > zone->getZoneDefPoints(whichZone)) {

			cout << endl << "Attack Successful!" << endl;

			int diff = (this->getAttackPoints() + zone->getZonePressureVal(whichZone)) - zone->getZoneDefPoints(whichZone);

			zone->lifePointsMinusOne();
			zone->pressureValSetZero(whichZone);
			zone->give3DefPoints(whichZone);

			for (int i = 0; i < diff; i++) {

				//to do 
			}

			this->changeAttackPoints(1);
			this->changeScore(1);
		}
		else {

			cout << "Attack Failed!" << endl;
			this->changeLifePoints(-1);

			if ((this->getLifePoints() % 10) == 0) {

				this->changeAttackPoints(-2);
			}
			zone->incPressureVal(whichZone);
		}

		if (zone->getLifePoints() <= 0) {

			return;
		}

		if (this->getLifePoints() <= 0) {

			cout << endl << "Hacker Dead!" << endl;
			return;
		}
	}
}
