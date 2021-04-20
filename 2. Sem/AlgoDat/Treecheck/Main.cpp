#include <iostream>
#include <string>
#include "Treecheck.h"

using namespace std;

string getFileName() {

	cout << "[TreeCheck 1.0]" << endl << endl;
	cout << "Programmaufruf: (treecheck) filename" << endl;
	cout << "-Integerschluesselwerte werden aus einem Textfile eingelesen-" << endl;

	string temp1, temp2;

	while (true) {

		cin >> temp1 >> temp2;

		if (temp1 != "treecheck") {
			cout << "Error!" << endl;
		}
		else {
			return temp2;
		}
	}
}

int main() {

	Treecheck* treecheck = new Treecheck();
	string filename = getFileName();
	treecheck->readFile(filename);

	return 0;
}
