#include "World.h"

World::World() {

	sizeX = 5;
	sizeY = 5;
	sizeZ = 10;

	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			for (int k = 0; k < sizeZ; k++) {

				worldArray[i][j][k] = rand() % 9 + 1;
			}
		}
	}
}

World::~World() {

	
}

void World::whichPlain() {

	int k = 0;

	while (true) {

		cout << "Which Plain would your like to Print? ";
		cin >> k;
		cout << endl;

		if ((k < 0) || (k > 9)) {
			cout << "[ERROR] The World only has 10 Plains! (0-9)" << endl << endl << endl;
		}
		else {
			printLayer(k);
		}
	}
}

void World::printLayer(int k) {

	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {

			cout << worldArray[i][j][k] << " ";
		}
		cout << endl;
	}
}

void World::printWorld(int n) {

	if (n < 10) {
		cout << "Layer " << n + 1 << ": " << endl;
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {

				cout << worldArray[i][j][n] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	printWorld(n + 1);
}