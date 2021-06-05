#include "server.h"

server::server() {

	lifePoints = 100;
	defensePoints = 20;
	pressureValue = 0;
}

server::~server() {


}

void server::changeDefensePoints(int x) {

	defensePoints += x;
}

void server::changeLifePoints(int x) {

	lifePoints += x;
}

void server::changePressureValue(int x) {

	pressureValue += x;
}

void server::setZero() {

	pressureValue = 0;
}

int server::getDefensePoints() {

	return this->defensePoints;
}

int server::getPressureValue() {

	return this->pressureValue;
}

int server::getLifePoints() {

	return this->lifePoints;
}

string server::getName() {

	return this->name;
}

defenseZone1::defenseZone1() {

	name = "DefenseZone1";
}

defenseZone1::~defenseZone1() {

	delete this;
}

void defenseZone1::beAttacked() {


}

defenseZone2::defenseZone2() {

	name = "DefenseZone2";
}

defenseZone2::~defenseZone2() {

	delete this;
}

void defenseZone2::beAttacked() {


}

defenseZone3::defenseZone3() {

	name = "DefenseZone3";
}

defenseZone3::~defenseZone3() {

	delete this;
}

void defenseZone3::beAttacked() {


}

defenseZone4::defenseZone4() {

	name = "DefenseZone4";
}

defenseZone4::~defenseZone4() {

	delete this;
}

void defenseZone4::beAttacked() {


}

defenseZone5::defenseZone5() {

	name = "DefenseZone5";
}

defenseZone5::~defenseZone5() {

	delete this;
}

void defenseZone5::beAttacked() {


}
