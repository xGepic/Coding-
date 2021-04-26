#include <iostream>
#include <string>
#include <cctype>
#include "TreeManager.h"

using namespace std;

int main() {

	int c = 0;

	TreeManager* tree = new TreeManager();
	TreeManager* subtree = new TreeManager();

	cout << "[TreeCheck]" << endl << endl;
	cout << "Programmaufruf: (treecheck) filename" << endl;
	cout << "Oder: " << endl;
	cout << "Programmaufruf: (treecheck) filename subtree-filename" << endl;
	cout << "-Integerschluesselwerte werden aus einem Textfile eingelesen-" << endl;

	string temp1 = "";
	string temp2 = "";
	string temp3 = "";
	string tooMuch = "";
	string temp;
	getline(std::cin, temp);

	 unsigned int i = 0;

	for (; i < temp.size() && temp[i] != ' '; i++) {

		temp1 += temp[i];
	}

	i++;

	for (; i < temp.size() && temp[i] != ' '; i++) {

		temp2 += temp[i];
	}

	i++;

	for (; i < temp.size() && temp[i] != ' '; i++) {

		temp3 += temp[i];
	}

	for (; i < temp.size(); i++) {

		tooMuch += temp[i];
	}

	if (tooMuch != "" || temp1 != "treecheck") {

		cout << "Invalid input" << endl;
	}
	else if (temp3 == "") {

		tree->readFile(temp2);
		tree->statisticsCheck();
	}
	else {

		tree->readFile(temp2);
		subtree->readFile(temp3);

		tree->searchSubtree(subtree->getRoot());
	}

	return 0;
}
