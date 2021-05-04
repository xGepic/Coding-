#include <iostream>
#include <time.h>
#include "World.h"

using namespace std;

int main() {

	srand((unsigned int)time(nullptr));

	World* myWorld = new World();
	myWorld->getMenu();

	Bot* Player1 = myWorld->chooseBot();
	Bot* Robot = myWorld->chooseRobot();

	myWorld->startGame(Player1, Robot);

	                                                                                            

	delete myWorld;
} 
