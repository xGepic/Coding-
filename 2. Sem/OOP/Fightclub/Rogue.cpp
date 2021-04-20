#include <Fighter.h>

Rogue::Rogue() : Fighter() {

	setLifepoints(7);
	setSpeed(4);
	setName("Rogue");
	setAmbushF();
	setAssassinateF();
	setCdF();
}

Rogue::~Rogue() {

	delete this;
}

void Rogue::setAmbushF() {

	ambush = false;
}

void Rogue::setAmbushT() {

	ambush = true;
}

void Rogue::setCdF() {

	cd = false;
}

void Rogue::setCdT() {

	cd = true;
}

void Rogue::setAssassinateF() {

	assassinate = false;
}

void Rogue::setAssassinateT() {

	assassinate = true;
}

void Rogue::useAbility(int n, Fighter* enemy, int p) {

	if (n == 4) {

		if (ambush == false) {

			if (p == 6) {

				cout << "Bot";
			}
			else {

				cout << "Player " << p;
			}
			cout << " used Ambush!";
			enemy->damage(4);
			Rogue::setAmbushT();
			Rogue::setCdF();
		}
		else {

			cout << "You cant use Ambush 2 Times in a Row!" << endl;
			Rogue::setAmbushF();
			Rogue::setCdF();
		}
	}
	if (n == 2) {

		if (p == 6) {

			cout << "Bot";
		}
		else {

			cout << "Player " << p;
		}
		cout << " used Backstab!";
		enemy->damage(2);
		Rogue::setCdF();
		Rogue::setAmbushF();
	}
	if (n == 3) {

		if (cd == false) {

			if (p == 6) {

				cout << "Bot";
			}
			else {

				cout << "Player " << p;
			}
			cout << " used Clever Disguise!";
			enemy->setDodge();
			Rogue::setCdT();
			Rogue::setAmbushF();
		}
		else {

			cout << "You cant use Clever Disguise 2 Times in a Row!" << endl;
			Rogue::setCdF();
		}
	}
	if (n == 1) {

		if (assassinate == false) {

			if (p == 6) {

				cout << "Bot";
			}
			else {

				cout << "Player " << p;
			}
			cout << " used Assassinate!";
			enemy->damage(5);
			Rogue::setAssassinateT();
			Rogue::setAmbushF();
			Rogue::setCdF();
		}
		else {

			cout << "You cant use Assassinate more than once per Game!" << endl;
		}
	}
}

void Rogue::printAbilities() {

	cout << endl;
	cout << "Assassinate		| Deal 5 Damage | Can only be used once" << endl;
	cout << "Backstab		| Deal 2 Damage " << endl;
	cout << "Clever Disguise		| Dodge your Opponent's next Move | Cant be used 2 Times in a Row" << endl;
	cout << "Ambush			| Deal 4 Damage | Cant be used 2 Times in a Row" << endl;
}
