#include <Fighter.h>

Hunter::Hunter() : Fighter() {

	setLifepoints(8);
	setSpeed(3);
	setName("Hunter");
}

Hunter::~Hunter() {

	delete this;
}

void Hunter::useAbility(int n, Fighter* enemy, int p) {

	if (n == 1) {

		if (p == 6) {

			cout << "Bot";
		}
		else {

			cout << "Player " << p;
		}
		cout << " used Steady Shot!";
		enemy->damage(2);
	}
	if (n == 2) {

		if (p == 6) {

			cout << "Bot";
		}
		else {

			cout << "Player " << p;
		}
		cout << " used Deadly Shot!";
		enemy->damage(3);
		Hunter::setOffline();
	}
	if (n == 3) {

		if (p == 6) {

			cout << "Bot";
		}
		else {

			cout << "Player " << p;
		}
		cout << " used Quick Shot!";
		enemy->damage(1);
		incSpeed();
	}
	if (n == 4) {

		if (p == 6) {

			cout << "Bot";
		}
		else {

			cout << "Player " << p;
		}
		cout << " used Healing Shot!";
		Hunter::heal(2);
	}
}

void Hunter::printAbilities() {

	cout << endl;
	cout << "Steady Shot		| Deal 2 Damage" << endl;
	cout << "Deadly Shot		| Deal 3 Damage but skip your next turn" << endl;
	cout << "Quick Shot		| Deal 1 Damage and increase your speed by 1" << endl;
	cout << "Healing Shot		| Increase your Health by 2" << endl;
}
