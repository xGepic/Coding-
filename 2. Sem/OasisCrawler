#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class node {
public:
	string Message;
	node* next = NULL;
};

void append(node** head, string newData) {

	node* newNode = new node();
	node* last = *head;
	newNode->Message = newData;
	newNode->next = NULL;

	if (*head == NULL) {
		*head = newNode;
		return;
	}
	while (last->next != NULL) {
		last = last->next;
	}
	last->next = newNode;
	return;
}

void printList(node* node) {

	int n = 1;
	cout << endl << "The game went as follows:" << endl;

	while (node != NULL) {
		cout << n << ". " << node->Message << endl;
		n++;
		node = node->next;
	}
	cout << endl << "Thank you for playing the Game!" << endl;
}

void freeList(node* head) {

	node* tmp;

	while (head != NULL) {
		tmp = head;
		head = head->next;
		delete(tmp);
	}
}

void throwError() {
	cout << endl;
	cout << "That is not possible!" << endl;
}

void getInfo() {
	cout << "--|OasisCrawler 2.0 by Stefan Simanek|--" << endl << endl;
	cout << "Welcome to the OasisCrawler! ";
	cout << "Find all Relics to win the game but be careful there are dangers lurking on the field!" << endl << endl;
	cout << "Move by typing in w, a, s, d -- ";
	cout << "If you want to end the game early, type in 'x'." << endl << endl;
}


class Character {
private:
	int LifePoints, RelicPoints, Strength, Agility, Intelligence;

public:
	int  X, Y;
	Character() {
		LifePoints = 5;
		RelicPoints = 0;
		Strength = 0;
		Agility = 0;
		Intelligence = 0;
		X = 0;
		Y = 0;
	}

	int getLifepoints() {
		return LifePoints;
	}

	int getRelicPoints() {
		return RelicPoints;
	}

	void damage(node** head) {
		LifePoints--;
		if (LifePoints == 0) {
			cout << endl << "Unfortunately you died!" << endl << endl;
			printList(*head);
			freeList(*head);
			exit(EXIT_SUCCESS);
		}
	}

	void heal() {
		LifePoints++;
	}

	void findRelic() {
		RelicPoints++;
	}

	int getStrength() {
		return Strength;
	}

	int getAgility() {
		return Agility;
	}

	int getIntelligence() {
		return Intelligence;
	}

	void campFire(char n) {

		if (n == 's') {
			Strength++;
		}
		if (n == 'a') {
			Agility++;
		}
		if (n == 'i') {
			Intelligence++;
		}
	}

	void printStats() {

		cout << endl;
		cout << "|Stats| - RelicPoints: " << getRelicPoints() << endl;
		cout << "|Stats| - Lifepoints: " << getLifepoints() << endl;
		cout << "|Stats| - Strength: " << getStrength() << endl;
		cout << "|Stats| - Agility: " << getAgility() << endl;
		cout << "|Stats| - Intelligence: " << getIntelligence() << endl;
		cout << endl;
	}
};

class World {
private:
	int rcg() {

		int n = rand() % 100 + 1;

		if (n <= 40) {
			return 'E';
		}
		if (n <= 80) {
			return 'D';
		}
		if (n <= 90) {
			return 'F';
		}
		else {
			return 'R';
		}
	}
public:
	char playingField[10][10];
	int RelicCount = 0;
	char guy = 'X';
	bool tmp = false;

	World() {
		while (tmp != true) {
			for (int x = 0; x < 10; x++) {
				for (int y = 0; y < 10; y++) {
					playingField[x][y] = rcg();
					if (playingField[x][y] == 'R') {
						RelicCount++;
					}
				}
			}
			if (RelicCount > 0) {
				tmp = true;
			}
		}
		playingField[0][0] = guy;
	}

	void printWorld(char Arr[10][10]) {
		cout << "+=====================+" << endl;
		for (int k = 0; k < 10; k++) {
			cout << "|" << " ";
			for (int l = 0; l < 10; l++) {
				cout << Arr[k][l] << " ";
			}
			cout << "|" << " ";
			cout << endl;
		}
		cout << "+=====================+" << endl;
	}

	void move(char Arr[10][10], int* x, int* y, char* guy, char temp, Character* C, node** head) {

		int n = rand() % 10;
		int m = rand() % 10;

		if (temp == 'w') {
			if (*x - 1 < 0) {
				throwError();
				return;
			}
			Arr[*x][*y] = 'E';
			*x = *x - 1;
			cout << "You took a step north!" << endl << endl;
			system("CLS");
			activate(Arr, x, y, C, head);
			Arr[*x][*y] = (*guy);
			if (Arr[n][m] == 'X') {
				cout << "The invisible enemy got you! [-1 LifePoint]" << endl;
				append(head, "The invisible enemy got you!");
				C->damage(head);
			}
			cout << "The invisible enemy is currently at [" << n << "][" << m << "]" << endl << endl;
			C->printStats();
			printWorld(Arr);
		}

		if (temp == 'a') {
			if (*y - 1 < 0) {
				throwError();
				return;
			}
			Arr[*x][*y] = 'E';
			*y = *y - 1;
			system("CLS");
			cout << "You took a step west!" << endl << endl;
			activate(Arr, x, y, C, head);
			Arr[*x][*y] = (*guy);
			if (Arr[n][m] == 'X') {
				cout << "The invisible enemy got you! [-1 LifePoint]" << endl;
				append(head, "The invisible enemy got you!");
				C->damage(head);
			}
			cout << "The invisible enemy is currently at [" << n << "][" << m << "]" << endl;
			C->printStats();
			printWorld(Arr);
		}

		if (temp == 's') {
			if (*x + 1 > 9) {
				throwError();
				return;
			}
			Arr[*x][*y] = 'E';
			*x = *x + 1;
			system("CLS");
			cout << "You took a step south!" << endl << endl;
			activate(Arr, x, y, C, head);
			Arr[*x][*y] = (*guy);
			if (Arr[n][m] == 'X') {
				cout << "The invisible enemy got you! [-1 LifePoint]" << endl;
				append(head, "The invisible enemy got you!");
				C->damage(head);
			}
			cout << "The invisible enemy is currently at [" << n << "][" << m << "]" << endl;
			C->printStats();
			printWorld(Arr);
		}

		if (temp == 'd') {
			if (*y + 1 > 9) {
				throwError();
				return;
			}
			Arr[*x][*y] = 'E';
			*y = *y + 1;
			system("CLS");
			cout << "You took a step east!" << endl << endl;
			activate(Arr, x, y, C, head);
			Arr[*x][*y] = (*guy);
			if (Arr[n][m] == 'X') {
				cout << "The invisible enemy got you! [-1 LifePoint]" << endl;
				append(head, "The invisible enemy got you!");
				C->damage(head);
			}
			cout << "The invisible enemy is currently at [" << *x << "][" << *y << "]" << endl;
			C->printStats();
			printWorld(Arr);
		}
	}

	void activate(char Arr[10][10], int* x, int* y, Character* C, node** head) {

		char n;
		int m = rand() % 4 + 1;

		if (Arr[*x][*y] == 'E') {
			cout << "You stepped on an empty field, nothing happens!" << endl << endl;
			if (m == 4) {
				cout << "You stumble past a Tavern! - Here you can improve 1 of your Skills!" << endl << endl;
				while (1) {
					cout << "Which Attribute whould you like to improve? [Strength(s), Agility(a) or Intelligence(i)]" << endl << endl;
					cin >> n;
					if (n == 's') {
						C->campFire(n);
						append(head, "You improved your Strength!");
						cout << "After hours of training you feel a lot stronger! [+1 Strength]" << endl << endl;
						break;
					}
					if (n == 'a') {
						C->campFire(n);
						append(head, "You improved your Agility!");
						cout << "You find green herbs that make you feel refreshed and rejuvenated! [+1 Agility]" << endl << endl;
						break;
					}
					if (n == 'i') {
						C->campFire(n);
						append(head, "You improved your Intelligence!");
						cout << "From your spellbook you study new sorceries! [+1 Intelligence] " << endl << endl;
						break;
					}
					else {
						throwError();
					}
				}
			}
		}
		if (Arr[*x][*y] == 'D') {
			cout << "You stepped on a danger field... ";
			int n = rand() % 6 + 1;
			if (n == 2) {
				if (C->getStrength() >= 2) {
					append(head, "You defeated an opponent!");
					cout << "but through your hard training you managed to defeat the Enemy!" << endl << endl;
				}
				else {
					C->damage(head);
					append(head, "You stepped on a danger field and got damaged!");
					cout << "and got damaged! [-1 LifePoint]" << endl << endl;
				}
			}
			else {
				cout << "but nothing happend!" << endl << endl;
				append(head, "You stepped on a danger field but nothing happend!");
			}
		}
		if (Arr[*x][*y] == 'F') {

			cout << "You stepped on a Fountain! - ";

			if (C->getIntelligence() >= 2) {
				C->heal(); C->heal();
				append(head, "You stepped on a Fountain and healed yourself!");
				cout << "With one of your spells you make the fountain more productive! [+2 LifePoints]" << endl << endl;
			}
			else {
				C->heal();
				append(head, "You stepped on a Fountain and healed yourself!");
				cout << "Take a rest and heal yourself! [+1 LifePoint]" << endl << endl;
			}
		}
		if (Arr[*x][*y] == 'R') {
			cout << "You stepped on a Relic! [+1 RelicPoint]" << endl;
			append(head, "You found a Relic!");
			C->findRelic();
			if (RelicCount == C->getRelicPoints()) {
				cout << "Congratulations you won the game!" << endl;
				printList(*head);
				freeList(*head);
				exit(EXIT_SUCCESS);
			}
		}
	}
};

int startGame(World* w, Character* c, node** head) {
	char x;
	cout << endl;
	cout << "You are at the 'X'" << endl;
	cout << "Where would you like to go?";
	cin >> x;
	if (x == 'w') {
		append(head, "You took a step north!");
		w->move(w->playingField, &c->X, &c->Y, &w->guy, x, c, head);
	}
	else if (x == 'd') {
		append(head, "You took a step east!");
		w->move(w->playingField, &c->X, &c->Y, &w->guy, x, c, head);
	}
	else if (x == 's') {
		append(head, "You took a step south!");
		w->move(w->playingField, &c->X, &c->Y, &w->guy, x, c, head);
	}
	else if (x == 'a') {
		append(head, "You took a step west!");
		w->move(w->playingField, &c->X, &c->Y, &w->guy, x, c, head);
	}
	else if (x == 'x') {
		cout << endl << "[Programm Terminated]" << endl;
		freeList(*head);
		exit(EXIT_SUCCESS);
	}
	else {
		throwError();
	}
}

int main() {

	srand((unsigned int)time(NULL));
	node* head = NULL;
	Character c;
	World w;
	getInfo();
	cout << "There are " << w.RelicCount << " Relics to be found!" << endl;
	c.printStats();
	w.printWorld(w.playingField);
	while (42) {

		startGame(&w, &c, &head);
	}
	return 0;
}
