#include <Fighter.h>

Custom::Custom() : Fighter() {

	setLifepoints(10);
	setSpeed(2);
	setName("Custom");
	setCounter(1);
	setCounterSpellF();
	setAmbushF();
	setAssassinateF();
	setCdF();
}

Custom::~Custom() {

	delete this;
}

void Custom::setCounter(int i) {

	counter = i;
}

int Custom::getCounter() {

	return this->counter;
}

void Custom::incCounter() {

	counter++;
}

void Custom::setCounterSpellF() {

	counterSpell = false;
}

void Custom::setCounterSpellT() {

	counterSpell = true;
}

void Custom::setAmbushF() {

	ambush = false;
}

void Custom::setAmbushT() {

	ambush = true;
}

void Custom::setCdF() {

	cd = false;
}

void Custom::setCdT() {

	cd = true;
}

void Custom::setAssassinateF() {

	assassinate = false;
}

void Custom::setAssassinateT() {

	assassinate = true;
}

void Custom::useAbility(int n, Fighter* enemy, int p) {

	if (n == 1) {
		cout << "Player " << p << " used Rage!";
		enemy->damage(1);
		incCounter();
	}
	if (n == 2) {
		cout << "Player " << p << " used Armor Up!";
		Custom::heal(2);
	}
	if (n == 3) {
		cout << "Player " << p << " used Tank Up!";
		Custom::heal(4);
		Custom::setOffline();
	}
	if (n == 4) {

		int temp;
		cout << "Player " << p << " used Execute!";
		if (getCounter() >= 4) {

			temp = enemy->getLifepoints();
			enemy->damage(temp);
		}
		else {

			cout << endl << "Rage has to be used at least 4 times in order to cast this!" << endl;
		}
	}
	if (n == 5) {
		cout << "Player " << p << " used Steady Shot!";
		enemy->damage(2);
	}
	if (n == 6) {
		cout << "Player " << p << " used Deadly Shot!";
		enemy->damage(3);
		Custom::setOffline();
	}
	if (n == 7) {
		cout << "Player " << p << " used Quick Shot!";
		enemy->damage(1);
		incSpeed();
	}
	if (n == 8) {
		cout << "Player " << p << " used Healing Shot!";
		Custom::heal(2);
	}
	if (n == 9) {
		cout << "Player " << p << " used Fireball!";
		enemy->damage(2);
		Custom::setCounterSpellF();
	}
	if (n == 10) {
		cout << "Player " << p << " used Frostbolt!";
		enemy->damage(1);
		enemy->decSpeed();
		Custom::setCounterSpellF();
	}
	if (n == 11) {
		cout << "Player " << p << " used Arcane Intellect!";
		enemy->damage(1);
		Custom::incSpeed();
		Custom::setCounterSpellF();
	}
	if (n == 12) {
		cout << "Player " << p << " used Counterspell!";
		if (counterSpell == false) {
			enemy->setNullify();
			Custom::setCounterSpellT();
		}
		else {
			cout << "You cant use Counterspell 2 Times in a Row!" << endl;
			Custom::setCounterSpellF();
		}
	}
	if (n == 13) {
		cout << "Player " << p << " used Ambush!";
		if (ambush == false) {
			enemy->damage(4);
			Custom::setAmbushT();
			Custom::setCdF();
		}
		else {
			cout << "You cant use Ambush 2 Times in a Row!" << endl;
			Custom::setAmbushF();
			Custom::setCdF();
		}
	}
	if (n == 14) {
		cout << "Player " << p << " used Backstab!";
		enemy->damage(2);
		Custom::setCdF();
		Custom::setAmbushF();
	}
	if (n == 15) {
		cout << "Player " << p << " used Clever Disguise!";
		if (cd == false) {
			enemy->setDodge();
			Custom::setCdT();
			Custom::setAmbushF();
		}
		else {
			cout << "You cant use Clever Disguise 2 Times in a Row!" << endl;
			Custom::setCdF();
		}
	}
	if (n == 16) {
		cout << "Player " << p << " used Assassinate!";
		if (assassinate == false) {
			enemy->damage(5);
			Custom::setAssassinateT();
			Custom::setAmbushF();
			Custom::setCdF();
		}
		else {

			cout << endl << "You cant use Assassinate more than once per Game!" << endl;
		}
	}
}

void Custom::printAbilities() {

	cout << "1. " << "Rage				| Deal 1 Damage." << endl;
	cout << "2. " << "Armor Up			| Increase your Health by 2" << endl;
	cout << "3. " << "Tank Up			| Increase your Health by 4 but skip your next turn" << endl;
	cout << "4. " << "Execute			| Kill your Opponent - Can only be used if you have used Rage 4 Times" << endl;
	cout << "5. " << "Steady Shot			| Deal 2 Damage" << endl;
	cout << "6. " << "Deadly Shot			| Deal 3 Damage but skip your next turn" << endl;
	cout << "7. " << "Quick Shot			| Deal 1 Damage and increase your speed by 1" << endl;
	cout << "8. " << "Healing Shot			| Increase your Health by 2" << endl;
	cout << "9. " << "Fireball			| Deal 2 Damage" << endl;
	cout << "10. " << "Frostbolt			| Deal 1 Damage and reduce your Opponent's Speed by 1" << endl;
	cout << "11. " << "Arcane Intellect		| Deal 1 Damage and Increase your Speed by 1" << endl;
	cout << "12. " << "Counterspell		| Nullify your Opponent's next Move | Cant be used 2 Times in a Row" << endl;
	cout << "13. " << "Ambush			| Deal 4 Damage | Cant be used 2 Times in a Row" << endl;
	cout << "14. " << "Backstab			| Deal 2 Damage " << endl;
	cout << "15. " << "Clever Disguise		| Dodge your Opponent's next Move | Cant be used 2 Times in a Row" << endl;
	cout << "16. " << "Assassinate			| Deal 5 Damage | Can only be used once" << endl;
}
