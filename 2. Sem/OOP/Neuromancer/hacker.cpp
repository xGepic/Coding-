#include "hacker.h"


hacker::hacker() {

	lifePoints = 100;
	attackPoints = 20;
	score = 0;
}

hacker::~hacker() {


}

void hacker::changeLifePoints(int x) {

	lifePoints += x;
}

void hacker::attack(int whichZone) {

	server* zone;
	int fail = rand() % 100 + 1;

	if (whichZone == 1) {

		zone = new defenseZone1();
	}
	if (whichZone == 2) {

		zone = new defenseZone2();
	}
	if (whichZone == 3) {

		zone = new defenseZone3();
	}
	if (whichZone == 4) {

		zone = new defenseZone4();
	}
	if (whichZone == 5) {

		zone = new defenseZone5();
	}

	if (fail == 1) {

		changeLifePoints(-5);
		cout << "Attack Failed" << endl;
		return;
	}


}