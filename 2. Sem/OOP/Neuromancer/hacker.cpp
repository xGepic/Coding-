#include "hacker.h"


hacker::hacker() {

	lifePoints = 100;
	attackPoints = 20;
	score = 0;
}

hacker::~hacker() {


}

void hacker::printStatus() {


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

void hacker::attack(int whichZone) {

	server* zone = nullptr;
	int fail = rand() % 100;

	cout << endl << "Zone " << whichZone << " is attacked!" << endl << endl;

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

	if (fail == 42) {

		changeLifePoints(-5);
		cout << "1 % Chance - Attack Failed" << endl;
		return;
	}

	while ((this->getLifePoints() >= 0) && (zone->getDefensePoints() >= 0)) {

		//cout << this->getAttackPoints() << " + " << zone->getPressureValue() << " > " << zone->getDefensePoints() << endl;

		if ((this->getAttackPoints() + zone->getPressureValue()) > zone->getDefensePoints()) {

			cout << endl << "Attack Successful!" << endl;

			int diff = (this->getAttackPoints() + zone->getPressureValue()) - zone->getDefensePoints();

			zone->changeLifePoints(-1);
			zone->setZero();
			zone->changeDefensePoints(3);

			for (int i = 0; i < diff; i++) {

				//to do 
			}
			this->changeAttackPoints(1);
			this->changeScore(1);
		}
		else {

			cout << endl << "Attack Failed!" << endl;
			this->changeLifePoints(-1);

			if ((this->getLifePoints() % 10) == 0) {

				this->changeAttackPoints(-2);
			}
			zone->changePressureValue(1);
		}
	}

	if (this->getLifePoints() <= 0) {

		cout << "Hacker Dead!" << endl;
		cout << endl << "Hacker Points: " << getScore() << endl;
		cout << endl << "Server Life: " << zone->getLifePoints() << endl;
	}

	if (zone->getDefensePoints() <= 0) {

		cout << "Server Dead!" << endl;
		cout << endl << "Hacker Points: " << getScore() << endl;
		cout << endl << "Server Life: " << zone->getLifePoints() << endl;
	}
}
