#include "Field.h"

Field::Field() {

	display = ' ';
	points = 0;
}

Field::~Field() {

}

void Field::displayField() {

	std::cout << display << " ";
}

int Field::getPoints() {

	return points;
}

void Field::setPoints(int x) {

	points = x;
}