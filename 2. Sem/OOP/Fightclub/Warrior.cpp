#include <Fighter.h>

Warrior::Warrior() : Fighter() {

	setLifepoints(15);
	setSpeed(1);
	setName("Warrior");
	setCounter(1);
}

Warrior::~Warrior() {

	delete this;
}

void Warrior::setCounter(int i) {

	counter = i;
}

int Warrior::getCounter() {

	return this->counter;
}

void Warrior::incCounter() {

	counter++;
}

void Warrior::useAbility(int n, Fighter* enemy, int p) {

	if (n == 1) {

		if (p == 6) {

			cout << "Bot";
		}
		else {

			cout << "Player " << p;
		}
		cout << " used Rage!";
		enemy->damage(1);
		incCounter();
	}
	if (n == 4) {

		if (p == 6) {

			cout << "Bot";
		}
		else {

			cout << "Player " << p;
		}
		cout << " used Armor Up!";
		Warrior::heal(2);
	}
	if (n == 3) {

		if (p == 6) {

			cout << "Bot";
		}
		else {

			cout << "Player " << p;
		}
		cout << " used Tank Up!";
		Warrior::heal(4);
		Warrior::setOffline();
	}
	if (n == 2) {

		int temp = 0;

		if (p == 6) {

			cout << "Bot";
		}
		else {

			cout << "Player " << p;
		}
		cout << " used Execute!";

		if (getCounter() >= 4) {

			temp = enemy->getLifepoints();
			enemy->damage(temp);
		}
		else {

			cout << endl << "Rage has to be used at least 4 times in order to cast this!" << endl;
		}
	}
}

void Warrior::printAbilities() {

	cout << endl;
	cout << "Rage		| Deal 1 Damage." << endl;
	cout << "Execute		| Kill your Opponent - Can only be used if you have used Rage 4 Times" << endl;
	cout << "Tank Up		| Increase your Health by 4 but skip your next turn" << endl;
	cout << "Armor Up	| Increase your Health by 2" << endl;
}
