#include "hacker.h"

hacker::hacker(string namee) {

	lifePoints = 100;
	attackPoints = 20;
	score = 0;
	name = namee;
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

string hacker::getName() {

	return this->name;
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

int hacker::rng(int x) {

	int temp = rand() % 5;

	if (temp == x) {

		rng(x);
	}

	return temp;
}

void hacker::attack(server* zone, int whichZone) {

	int fail = rand() % 100;

	if (fail == 42) {

		changeLifePoints(-5);
		cout << "1 % Chance - Attack Failed" << endl;
		return;
	}

	while (true) {

		//cout << this->getAttackPoints() << " + " << zone->getZonePressureVal(whichZone) << " < " << zone->getZoneDefPoints(whichZone) << endl;

		cout << this->getName() << " - ";

		if ((this->getAttackPoints() + zone->getZonePressureVal(whichZone)) > zone->getZoneDefPoints(whichZone)) {

			cout << "Attack Successful!" << endl;

			int diff = (this->getAttackPoints() + zone->getZonePressureVal(whichZone)) - zone->getZoneDefPoints(whichZone);

			m.lock();

			zone->lifePointsMinusOne();
			zone->pressureValSetZero(whichZone);
			zone->giveDefPoints(whichZone);

			int tempZone = rng(whichZone);

			while (diff > 0) {

				if (zone->getZoneDefPoints(tempZone) < 2) {

					if (tempZone + 1 > 4) {

						if (whichZone == 0) {

							tempZone = 1;
						}
						else {

							tempZone = 0;
						}
					}
					else {

						if (tempZone + 1 == whichZone) {

							if (tempZone + 2 > 4) {

								tempZone = 0;
							}
							else {

								tempZone += 2;
							}
						}
						else {

							tempZone++;
						}
					}
				}
				zone->decZoneDefPoints(tempZone);
				zone->incZoneDefPoints(whichZone);
				diff--;
			}

			m.unlock();

			this->changeAttackPoints(3);
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

			cout << endl << this->getName() << " Dead!" << endl;
			return;
		}
	}
}
