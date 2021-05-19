#include <iostream>
#include <chrono>
#include <thread>
#include "world.h"

using namespace std;

int main() {

	auto startTime = chrono::steady_clock::now();

	srand((unsigned int)time(NULL));

	World* world = new World();
	BotOne* player1 = new BotOne();
	BotTwo* player2 = new BotTwo();

	thread th0(&World::startGame, world, player1, player2);
	th0.join();

	auto endTime = chrono::steady_clock::now();
	auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
	cout << endl << "Time Elapsed: "<< elapsed << " MS" << endl;
}
