#include <Fighter.h>

Fighter::Fighter() {

	LifePoints = 0;
	Speed = 0;
	isOnline = true;
	nullify = false;
	dodge = false;
}

Fighter::~Fighter() {


}

void Fighter::setLifepoints(int lp) {

	LifePoints = lp;
}

int Fighter::getLifepoints() {

	return this->LifePoints;
}

void Fighter::setSpeed(int s) {

	Speed = s;
}

int Fighter::getSpeed() {

	return this->Speed;
}

void Fighter::setName(string n) {

	name = n;
}

string Fighter::getName() {

	return this->name;
}

void Fighter::heal(int i) {

	cout << " [+" << i << " Lifepoint(s)]" << endl;
	this->LifePoints += i;
}

void Fighter::damage(int i) {

	cout << " [-" << i << " Lifepoint(s)]" << endl;
	this->LifePoints -= i;
}

void Fighter::setOnline() {

	isOnline = true;
}

void Fighter::setOffline() {

	isOnline = false;
}

void Fighter::incSpeed() {

	Speed++;
}

void Fighter::decSpeed() {

	Speed--;
}

void Fighter::setNullify() {

	nullify = true;
}

void Fighter::unNullify() {

	nullify = false;
}

void Fighter::setDodge() {

	dodge = true;
}

void Fighter::unDodge() {

	dodge = false;
}
