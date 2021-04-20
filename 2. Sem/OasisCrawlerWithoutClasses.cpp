#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef struct Spielwelt {
	char spielfelder[5][5];
}Spielwelt;

typedef struct Character {
	int LifePoints = 2;
	int RelicPoints = 0;
}Charakter;

typedef struct node {
	string Message;
	node* next = NULL;
}node;

void freeList(node* head) {

	node* tmp;

	while (head != NULL) {
		tmp = head;
		head = head->next;
		delete(tmp);
	}
}

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
	cout << "Thank you for playing the Game!" << endl;
}

int countRelics(char Arr[5][5]) {

	int h = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (Arr[i][j] == 'R') {
				h++;
			}
		}
	}
	return h;
}

void damageHealRelic(Character* C, char field, char Arr[5][5], node** head) {

	if (field == 'D') {
		C->LifePoints--;

		if (C->LifePoints == 0) {
			cout << "Unfortunately you died!" << endl;
			printList(*head);
			freeList(*head);
			exit(EXIT_SUCCESS);
		}
	}
	if (field == 'F') {
		C->LifePoints++;
	}
	if (field == 'R') {
		C->RelicPoints++;
	}
}

void getInfo() {
	cout << "--|OasisCrawler 1.0 by Stefan Simanek|--" << endl << endl;
	cout << "Welcome to the OasisCrawler! ";
	cout << "Find all Relics to win the game but be careful there are dangers lurking on the field!" << endl << endl;
	cout << "Move by typing in w, a, s, d -- ";
	cout << "If you want to end the game early, type in 'x'." << endl << endl;
}

void throwError() {
	cout << endl;
	cout << "That is not possible!" << endl;
}

void activate(char Arr[5][5], int* i, int* j, Character* C, int relics, node** head) {

	char danger = 'D';
	char fountain = 'F';
	char relic = 'R';

	if (Arr[*i][*j] == 'E') {
		append(head, "You stepped on an empty field, nothing happened!");
		cout << "You stepped on an empty field, nothing happens!" << endl;
	}
	if (Arr[*i][*j] == 'D') {
		cout << "You stepped on a danger field ";
		int n = rand() % 6 + 1;
		if (n == 6) {
			cout << "and got damaged! [-1 LifePoint]" << endl;
			append(head, "You stepped on a danger field and got damaged!");
			damageHealRelic(C, danger, Arr, head);
			cout << "You have " << C->LifePoints << " LifePoint(s) left!" << endl;
		}
		else {
			cout << "but nothing happend!" << endl;
			append(head, "You stepped on a danger field but nothing happend!");
		}
	}
	if (Arr[*i][*j] == 'F') {
		cout << "You stepped on a Fountain! Take a rest and heal yourself! [+1 LifePoint]" << endl;
		append(head, "You stepped on a Fountain and healed yourself!");
		damageHealRelic(C, fountain, Arr, head);
		cout << "You have " << C->LifePoints << " LifePoint(s) left!" << endl;
	}
	if (Arr[*i][*j] == 'R') {
		cout << "You stepped on a Relic! [+1 RelicPoint]" << endl;
		append(head, "You found a Relic!");
		damageHealRelic(C, relic, Arr, head);
		if (C->RelicPoints == relics) {
			cout << "Congratulations you won the game!" << endl;
			printList(*head);
			freeList(*head);
			exit(EXIT_SUCCESS);
		}
		cout << "You have " << C->RelicPoints << " RelicPoint(s) so far!" << endl;
	}
}

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

void initArray(char Arr[5][5]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			Arr[i][j] = rcg();
		}
	}
	Arr[0][0] = 'E';
	Arr[2][2] = 'R';
}

void printArray(char Arr[5][5]) {
	cout << "+===========+" << endl;
	for (int k = 0; k < 5; k++) {
		cout << "|" << " ";
		for (int l = 0; l < 5; l++) {
			cout << Arr[k][l] << " ";
		}
		cout << "|" << " ";
		cout << endl;
	}
	cout << "+===========+" << endl;
}

void north(char Arr[5][5], int* i, int* j, char* guy, Character* C, int relics, node** head) {

	int n = rand() % 5;
	int m = rand() % 5;
	char damage = 'D';

	if (*i - 1 < 0) {
		throwError();
		return;
	}
	cout << endl;
	cout << "You took a step north!" << endl;
	Arr[*i][*j] = 'E';
	*i = *i - 1;
	activate(Arr, i, j, C, relics, head);
	Arr[*i][*j] = (*guy);
	if (Arr[n][m] == 'X') {
		cout << "The invisible enemy got you! [-1 LifePoint]" << endl;
		append(head, "The invisible enemy got you!");
		damageHealRelic(C, damage, Arr, head);
		cout << "You have " << C->LifePoints << " LifePoint(s) left!" << endl;
	}
	cout << "The invisible enemy is currently at [" << n << "][" << m << "]" << endl;
	printArray(Arr);
}

void east(char Arr[5][5], int* i, int* j, char* guy, Character* C, int relics, node** head) {

	int n = rand() % 5;
	int m = rand() % 5;
	char damage = 'D';

	if (*j + 1 > 4) {
		throwError();
		return;
	}
	cout << endl;
	cout << "You took a step east!" << endl;
	Arr[*i][*j] = 'E';
	*j = *j + 1;
	activate(Arr, i, j, C, relics, head);
	Arr[*i][*j] = (*guy);
	if (Arr[n][m] == 'X') {
		cout << "The invisible enemy got you! [-1 LifePoint]" << endl;
		append(head, "The invisible enemy got you!");
		damageHealRelic(C, damage, Arr, head);
		cout << "You have " << C->LifePoints << " LifePoint(s) left!" << endl;
	}
	cout << "The invisible enemy is currently at [" << n << "][" << m << "]" << endl;
	printArray(Arr);
}

void south(char Arr[5][5], int* i, int* j, char* guy, Character* C, int relics, node** head) {

	int n = rand() % 5;
	int m = rand() % 5;
	char damage = 'D';

	if (*i + 1 > 4) {
		throwError();
		return;
	}
	cout << endl;
	cout << "You took a step south!" << endl;
	Arr[*i][*j] = 'E';
	*i = *i + 1;
	activate(Arr, i, j, C, relics, head);
	Arr[*i][*j] = (*guy);
	if (Arr[n][m] == 'X') {
		cout << "The invisible enemy got you! [-1 LifePoint]" << endl;
		append(head, "The invisible enemy got you!");
		damageHealRelic(C, damage, Arr, head);
		cout << "You have " << C->LifePoints << " LifePoint(s) left!" << endl;
	}
	cout << endl << "The invisible enemy is currently at [" << n << "][" << m << "]" << endl;
	printArray(Arr);
}

void west(char Arr[5][5], int* i, int* j, char* guy, Character* C, int relics, node** head) {

	int n = rand() % 5;
	int m = rand() % 5;
	char damage = 'D';

	if (*j - 1 < 0) {
		throwError();
		return;
	}
	cout << endl;
	cout << "You took a step west!" << endl;
	Arr[*i][*j] = 'E';
	*j = *j - 1;
	activate(Arr, i, j, C, relics, head);
	Arr[*i][*j] = (*guy);
	if (Arr[n][m] == 'X') {
		cout << "The invisible enemy got you! [-1 LifePoint]" << endl;
		append(head, "The invisible enemy got you!");
		damageHealRelic(C, damage, Arr, head);
		cout << "You have " << C->LifePoints << " LifePoint(s) left!" << endl;
	}
	cout << "The invisible enemy is currently at [" << n << "][" << m << "]" << endl;
	printArray(Arr);
}

int main() {

	node* head = NULL;
	srand((unsigned int)time(NULL));
	Spielwelt s;
	Character C;
	char x;
	int i = 0;
	int j = 0;
	int run = 42;
	char guy = 'X';
	initArray(s.spielfelder);
	s.spielfelder[0][0] = guy;
	getInfo();
	cout << "You have 2 LifePoints and ";
	int relics = countRelics(s.spielfelder);
	cout << "there are " << relics << " Relics to be found!" << endl;
	printArray(s.spielfelder);

	while (run) {

		cout << endl;
		cout << "You are at the 'X'" << endl;
		cout << "Where would you like to go?";
		cin >> x;

		if (x == 'w') {
			append(&head, "You took a step north!");
			north(s.spielfelder, &i, &j, &guy, &C, relics, &head);
		}
		else if (x == 'd') {
			append(&head, "You took a step east!");
			east(s.spielfelder, &i, &j, &guy, &C, relics, &head);
		}
		else if (x == 's') {
			append(&head, "You took a step south!");
			south(s.spielfelder, &i, &j, &guy, &C, relics, &head);
		}
		else if (x == 'a') {
			append(&head, "You took a step west!");
			west(s.spielfelder, &i, &j, &guy, &C, relics, &head);
		}
		else if (x == 'x') {
			cout << "[Programm Terminated]" << endl;
			freeList(head);
			exit(EXIT_SUCCESS);
		}
		else {
			throwError();
		}
	}
}
