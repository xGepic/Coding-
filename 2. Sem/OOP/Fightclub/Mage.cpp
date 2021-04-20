#include <Fighter.h>

Mage::Mage() : Fighter() {

	setLifepoints(12);
	setSpeed(2);
	setName("Mage");
	setCounterSpellF();
}

Mage::~Mage() {

	delete this;
}

void Mage::setCounterSpellF() {

	counterSpell = false;
}

void Mage::setCounterSpellT() {

	counterSpell = true;
}

void Mage::useAbility(int n, Fighter* enemy, int p) {

	if (n == 1) {

		if (p == 6) {

			cout << "Bot";
		}
		else {

			cout << "Player " << p;
		}
		cout << " used Fireball!";
		enemy->damage(2);
		Mage::setCounterSpellF();
	}
	if (n == 2) {

		if (p == 6) {

			cout << "Bot";
		}
		else {

			cout << "Player " << p;
		}
		cout << " used Frostbolt!";
		enemy->damage(1);
		enemy->decSpeed();
		Mage::setCounterSpellF();
	}
	if (n == 3) {

		if (p == 6) {

			cout << "Bot";
		}
		else {

			cout << "Player " << p;
		}
		cout << " used Arcane Intellect!";
		enemy->damage(1);
		Mage::incSpeed();
		Mage::setCounterSpellF();
	}
	if (n == 4) {

		if (counterSpell == false) {

			if (p == 6) {

				cout << "Bot";
			}
			else {

				cout << "Player " << p;
			}
			cout << " used Counterspell!";
			enemy->setNullify();
			Mage::setCounterSpellT();
		}
		else {

			cout << "You cant use Counterspell 2 Times in a Row!" << endl;
			Mage::setCounterSpellF();
		}
	}
}

void Mage::printAbilities() {

	cout << endl;
	cout << "Fireball		| Deal 2 Damage" << endl;
	cout << "Frostbolt		| Deal 1 Damage and reduce your Opponent's Speed by 1" << endl;
	cout << "Arcane Intellect	| Deal 1 Damage and Increase your Speed by 1" << endl;
	cout << "Counterspell		| Nullify your Opponent's next Move | Cant be used 2 Times in a Row" << endl;
}
