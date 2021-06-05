#include <iostream>
#include <thread>
#include <chrono>
#include "hacker.h"
#include "server.h"

using namespace std;

mutex m;

int rng() {

	return rand() % 5;
}

int main() {

	cout << "--| Neuromancer 1.0 by Stefan Simanek |--" << endl << endl;

	srand((unsigned int)time(NULL));
	auto startTime = chrono::steady_clock::now();

	server* Server = new server();
	hacker* h1 = new hacker();
	hacker* h2 = new hacker();
	hacker* h3 = new hacker();
	hacker* h4 = new hacker();
	hacker* h5 = new hacker();

	thread hacker1(&hacker::attack, h1, ref(Server), rng());
	thread hacker2(&hacker::attack, h2, ref(Server), rng());
	thread hacker3(&hacker::attack, h3, ref(Server), rng());
	thread hacker4(&hacker::attack, h4, ref(Server), rng());
	thread hacker5(&hacker::attack, h5, ref(Server), rng());
	hacker1.join();
	hacker2.join();
	hacker3.join();
	hacker4.join();
	hacker5.join();

	if ((h1->getLifePoints() <= 0) && (h2->getLifePoints() <= 0) && (h3->getLifePoints() <= 0) && (h4->getLifePoints() <= 0) && (h5->getLifePoints() <= 0)) {

		cout << endl << "Server Won!" << endl;
	}

	if (Server->getLifePoints() <= 0) {

		cout << endl << "Hackers Won!" << endl;
	}

	int sum = h1->getScore() + h2->getScore() + h3->getScore() + h4->getScore() + h5->getScore();
	cout << endl << "Accumulated Points: " << sum << endl;

	auto endTime = chrono::steady_clock::now();
	auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
	cout << endl << "Elapsed Time: " << elapsed << " Milliseconds" << endl;

	delete h1;
	delete h2;
	delete h3;
	delete h4;
	delete h5;
	delete Server;
	return 0;
}
