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

defenseZone1::defenseZone1() {


}

defenseZone1::~defenseZone1() {

	delete this;
}

void defenseZone1::beAttacked() {


}

defenseZone2::defenseZone2() {


}

defenseZone2::~defenseZone2() {

	delete this;
}

void defenseZone2::beAttacked() {


}

defenseZone3::defenseZone3() {


}

defenseZone3::~defenseZone3() {

	delete this;
}

void defenseZone3::beAttacked() {


}

defenseZone4::defenseZone4() {


}

defenseZone4::~defenseZone4() {

	delete this;
}

void defenseZone4::beAttacked() {


}

defenseZone5::defenseZone5() {


}

defenseZone5::~defenseZone5() {

	delete this;
}

void defenseZone5::beAttacked() {


}
