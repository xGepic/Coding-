#include "Player.h"

Player::Player() {

	stamina = 0;
	points = 0;
	defensePoints = 0;
	attackBonus = 0;
	attackPoints = 0;
}

Player::Player(std::string name) {

	this->name = name;
}

Player::~Player() {

}

int Player::getPoints() {

	return points;
}

int Player::getAttack() {

	return attackPoints;
}

int Player::getDefense() {

	return defensePoints;
}

std::string Player::getName() {

	return name;
}

void Player::rest() {

	stamina = 100;
	attackBonus = 0;
}

bool Player::operator >(Player* P) {

	Player* temp = this;
	int firstValue = temp->getPoints();
	int secondValue = P->getPoints();

	if (firstValue == NULL) {
		throw invalid_argument("Input Failed!");
	}

	if (firstValue > secondValue) {
		return true;
	}
	else {
		return false;
	}
}

PlayerA::PlayerA(string n) {

	attackBonus = 0;
	attackPoints = 40;
	defensePoints = 60;
	name = n;
	points = 0;
	stamina = 100;
}

bool PlayerA::attack(Player* opponent) {

	int temp = rand() % 4 + 1;
	attackBonus += temp;

	if (opponent == NULL) {

		throw invalid_argument("Input Failed!");
	}

	double tmpAttackValue = attackBonus + attackPoints * opponent->beAttacked();

	if (tmpAttackValue > opponent->getDefense()) {

		points++;
		return true;
	}
	else {
		return false;
	}
}

double PlayerA::beAttacked() {

	if ((stamina - 3) < 0) {

	}
	else {

		stamina -= 3;
	}
	if (stamina % 7 == 0) {

		return 5;
	}
	if (stamina % 5 == 0) {

		return 3;
	}
	if (stamina % 2 == 0) {

		return 1;
	}
	else {

		return 0;
	}
}

PlayerB::PlayerB(string n) {

	attackBonus = 0;
	attackPoints = 45;
	defensePoints = 55;
	confused = false;
	name = n;
	points = 0;
	stamina = 100;
}

bool PlayerB::attack(Player* opponent) {

	int temp = rand() % 10 + 1;

	if (opponent == NULL) {

		throw invalid_argument("Input Failed!");
	}

	if (temp < 4) {

		if (confused == false) {
			confused = true;
		}
		if (confused == true) {
			confused = false;
		}
	}
	if (confused == false) {

		attackBonus += static_cast<int>((opponent->beAttacked()) * 5);

		int tmpAttackValue = attackBonus + attackPoints;

		if (tmpAttackValue > opponent->getDefense()) {

			points++;
			return true;
		}
		else {

			return false;
		}
	}
	else {
		return false;
	}
}

double PlayerB::beAttacked() {

	if (confused == true) {

		stamina -= stamina / 5;
	}
	else {

		stamina -= stamina / 20;
	}

	if (stamina > 30) {

		return 0;
	}
	else {

		return 1;
	}
}
