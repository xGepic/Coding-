#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include "hacker.h"

using namespace std;

mutex m;

int rng() {

	return rand() % 5 + 1;
}

int main() {

	srand((unsigned int)time(NULL));
	auto startTime = chrono::steady_clock::now();

	thread hacker1(&hacker::attack, hacker(), rng());
	thread hacker2(&hacker::attack, hacker(), rng());
	thread hacker3(&hacker::attack, hacker(), rng());
	thread hacker4(&hacker::attack, hacker(), rng());
	thread hacker5(&hacker::attack, hacker(), rng());
	hacker1.join();
	hacker2.join();
	hacker3.join();
	hacker4.join();
	hacker5.join();

	auto endTime = chrono::steady_clock::now();
	auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << "Elapsed Time: " << elapsed << " Milliseconds" << endl;

	return 0;
}
