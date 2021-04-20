#include <iostream>
#include <string>
#include <conio.h>
#include <cmath>
#include "Hashtable.h"

using namespace std;

char getMenu();

int main()
{
	// Hashtable
	Hashtable* myTable = new Hashtable();
	// fuer getMenu()
	char action;
	// ob eine Funtkion erfolgreich ausgefuehrt wurde oder nicht
	bool success = true;
	do {
		action = getMenu();
		switch (action) {
		case('A'):  success = myTable->addAktie();
			break;
		case('D'):  success = myTable->delAktie();
			break;
		case('I'):  success = myTable->importAktie();
			break;
		case('C'):  success = myTable->searchAktie();
			break;
		case('P'):  success = myTable->plotAktie();
			break;
		case('S'):  success = myTable->saveHashtableTo();
			break;
		case('L'):  cout << "Hastable wird geloescht..." << endl;
			delete myTable;
			myTable = new Hashtable();
			success = myTable->loadHashtableFrom();
			break;
		default:    break;
		}
		if (!success) {
			cout << "Ihre Funktion konnte nicht erfolgreich ausgefuehrt werden." << endl;
		}

	} while (action != 'Q');

	// Speicherplatz freigeben
	delete myTable;

	return 0;
}

char getMenu() {

	char action;
	while (1) {
		cout << "Option auswahlen:" << endl
			<< "(A) ADD  - Aktie zu Hashtable hinzufuegen." << endl
			<< "(D) DEL - Aktie aus Hashtable loeschen." << endl
			<< "(I) IMPORT -  Kurswerte fuer Aktie aus csv Datei importieren." << endl
			<< "(C) SEARCH - Nach Aktie suchen und neuesten Eintrag ausgeben." << endl
			<< "(P) PLOT - Schlusskurse der letzten 30 Tage." << endl
			<< "(S) SAVE - Hashtable in txt Datei speichern." << endl
			<< "(L) LOAD - Hashtable aus txt Datei laden." << endl
			<< "(Q) QUIT - Programm beenden." << endl;
		cin >> action;
		action = toupper(action);
		switch (action) {
		case('A'):
		case('D'):
		case('I'):
		case('C'):
		case('P'):
		case('S'):
		case('L'):
		case('Q'):  return action;
		default:    cout << "Invalid selection" << endl;
			break;
		}
	}
}
