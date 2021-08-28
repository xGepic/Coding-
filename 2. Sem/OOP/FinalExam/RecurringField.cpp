#include "RecurringField.h"

RecurringField::RecurringField() {

	points = rand() % 3 + 1;
	display = 'O';
}

bool RecurringField::execute() {

	points -= 1;
	return true;
}