#include "World.h"

World::World() {

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			if (rng() == 0) {

				worldArr[i][j] = new RecurringField();
			}
			if (rng() == 1) {

				worldArr[i][j] = new PlainField();
			}
		}
	}
}

World::~World() {

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			delete worldArr[i][j];
		}
	}
}

void World::printWorld() {

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			worldArr[i][j]->displayField();
		}
		cout << endl;
	}
}

void World::executeField(int x, int y) {

	if ((x > 2) || (y > 2)) {

		throw invalid_argument("X oder Y Wert zu groß");
	}

	if (worldArr[x][y]->execute() == true) {

		if (worldArr[x][y]->getPoints() > 0) {

			RecurringField* temp = new RecurringField();
			temp->setPoints(worldArr[x][y]->getPoints());

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {

					if (typeid(worldArr[i][j]) == typeid(PlainField)) {
						worldArr[i][j] = temp;
					}
				}
			}
			
			worldArr[x][y] = new PlainField();
		}
	}
}

bool World::isEmpty() {

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			if (typeid(worldArr[i][j]) == typeid(RecurringField)) {

				return false;
			}
		}
	}
	return true;
}

int World::rng() {

	return rand() % 2;
}