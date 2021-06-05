#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>
#include "hacker.h"
#include "server.h"

using namespace std;

mutex m;

server* rng() {

	int temp = rand() % 5 + 1;

	if (temp == 1) {

		return new defenseZone1();
	}
	if (temp == 2) {

		return new defenseZone2();
	}
	if (temp == 3) {

		return new defenseZone3();
	}
	if (temp == 4) {

		return new defenseZone4();
	}
	if (temp == 5) {

		return new defenseZone5();
	}
	else {
		return nullptr;
	}
}

int main() {

	cout << "--| Neuromancer 1.0 by Stefan Simanek |--" << endl << endl;

	srand((unsigned int)time(NULL));
	auto startTime = chrono::steady_clock::now();

	hacker* h1 = new hacker();
	hacker* h2 = new hacker();
	hacker* h3 = new hacker();
	hacker* h4 = new hacker();
	hacker* h5 = new hacker();

	thread hacker1(&hacker::attack, h1, rng());
	thread hacker2(&hacker::attack, h2, rng());
	thread hacker3(&hacker::attack, h3, rng());
	thread hacker4(&hacker::attack, h4, rng());
	thread hacker5(&hacker::attack, h5, rng());
	hacker1.join();
	hacker2.join();
	hacker3.join();
	hacker4.join();
	hacker5.join();

	auto endTime = chrono::steady_clock::now();
	auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count(); 
	cout << endl << "Elapsed Time: " << elapsed << " Milliseconds" << endl;

	delete h1;
	delete h2;
	delete h3;
	delete h4;
	delete h5;
	return 0;
}
