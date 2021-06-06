#include <iostream>
#include <thread>
#include <chrono>
#include "hacker.h"
#include "server.h"

using namespace std;

int rng() {

	return rand() % 5;
}

void printStatus(hacker* h1, hacker* h2, hacker* h3, hacker* h4, hacker* h5, server* Server) {

	int sum = h1->getScore() + h2->getScore() + h3->getScore() + h4->getScore() + h5->getScore();

	cout << "[STATUS]" << endl;
	cout << "Hacker1 LP: " << h1->getLifePoints() << "  " << "Hacker1 Points: " << h1->getScore() << endl;
	cout << "Hacker2 LP: " << h2->getLifePoints() << "  " << "Hacker2 Points: " << h2->getScore() << endl;
	cout << "Hacker3 LP: " << h3->getLifePoints() << "  " << "Hacker3 Points: " << h3->getScore() << endl;
	cout << "Hacker4 LP: " << h4->getLifePoints() << "  " << "Hacker4 Points: " << h4->getScore() << endl;
	cout << "Hacker5 LP: " << h5->getLifePoints() << "  " << "Hacker5 Points: " << h5->getScore() << endl;

	cout << endl << "Server Lifepoints: " << Server->getLifePoints() << endl;
	cout << "Accumulated Points: " << sum << endl;
}

int main() {

	cout << "--| Neuromancer 1.0 by Stefan Simanek |--" << endl << endl;

	srand((unsigned int)time(NULL));
	auto startTime = chrono::steady_clock::now();

	server* Server = new server();
	hacker* h1 = new hacker("Hacker1");
	hacker* h2 = new hacker("Hacker2");
	hacker* h3 = new hacker("Hacker3");
	hacker* h4 = new hacker("Hacker4");
	hacker* h5 = new hacker("Hacker5");

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

		cout << endl << endl << "Server Won!" << endl << endl;
		printStatus(h1, h2, h3, h4, h5, Server);
	}

	if (Server->getLifePoints() <= 0) {

		cout << endl << "Hackers Won!" << endl << endl;
		printStatus(h1, h2, h3, h4, h5, Server);
	}

	auto endTime = chrono::steady_clock::now();
	auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
	cout << endl << endl << "Elapsed Time: " << elapsed << " Milliseconds" << endl;

	delete h1;
	delete h2;
	delete h3;
	delete h4;
	delete h5;
	delete Server;
	return 0;
}
