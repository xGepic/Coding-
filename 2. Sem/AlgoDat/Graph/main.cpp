#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include "AdjazenzListe.h"
#include "AdjazenzManager.h"

using namespace std;

void getMenu() {

	cout << "[Find Path]" << endl << endl;
	cout << "Programmaufruf: (find_path) filename_graph start ziel" << endl;
	cout << "Der Graph wird aus dem Input-File gelsen und gespeichert. Anschliessend wird der kuerzeste Weg berechnet." << endl;
}

int main() {

	AdjazenzManager* manager = new AdjazenzManager();
	unsigned int i = 0;
	string input, command, filename, temp1, temp2, temp3, temp4, excess_input;

	getMenu();
	getline(cin, input);

	for (; i < input.size() && input[i] != ' '; i++) {

		command += input[i];
	}
	i++;

	for (; i < input.size() && input[i] != ' '; i++) {

		filename += input[i];
	}
	i++;

	for (; i < input.size() && input[i] != ' '; i++) {

		temp1 += input[i];
	}
	i++;

	for (; i < input.size() && input[i] != ' '; i++) {

		temp2 += input[i];
	}
	i++;

	for (; i < input.size() && input[i] != ' '; i++) {

		temp3 += input[i];
	}
	i++;

	for (; i < input.size() && input[i] != ' '; i++) {

		temp4 += input[i];
	}
	i++;

	for (; i < input.size(); i++) {

		excess_input += input[i];
	}

	if (excess_input != "" || command != "find_path") {

		cout << "Invalid Input!" << endl;
	}
	else {

		if (temp4 != "") {

			auto startTime = chrono::steady_clock::now();
			manager->readFile(filename);
			manager->dijkstra(temp1 + " " + temp2, temp3 + " " + temp4);
			auto endTime = chrono::steady_clock::now();
			auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
			cout << endl << "Elapsed time: " << elapsed << " MS" << endl;
		}
		else if (temp3 != "") {

			if (manager->existsInList(temp1 + " " + temp2)) {

				auto startTime = chrono::steady_clock::now();
				manager->readFile(filename);
				manager->dijkstra(temp1 + " " + temp2, temp3);
				auto endTime = chrono::steady_clock::now();
				auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
				cout << endl << "Elapsed time: " << elapsed << " MS" << endl;
			}
			else {

				auto startTime = chrono::steady_clock::now();
				manager->readFile(filename);
				manager->dijkstra(temp1, temp2 + " " + temp3);
				auto endTime = chrono::steady_clock::now();
				auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
				cout << endl << "Elapsed time: " << elapsed << " MS" << endl;
			}
		}
		else {

			auto startTime = chrono::steady_clock::now();
			manager->readFile(filename);
			manager->dijkstra(temp1, temp2);
			auto endTime = chrono::steady_clock::now();
			auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
			cout << endl << "Elapsed time: " << elapsed << " MS" << endl;
		}
	}
	return 0;
}
