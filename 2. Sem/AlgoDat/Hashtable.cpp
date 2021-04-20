#include "Hashtable.h"
#include <cmath>

// Konstruktor
Hashtable::Hashtable()
{
	anzahlAktien = 0;
	isFree = new bool[1019];
	for (int i = 0; i < 1019; i++)
	{
		isFree[i] = true;
	}
	hTable = new Aktie * [1019];
	for (int i = 0; i < 1019; i++)
	{
		hTable[i] = nullptr;
	}
}

// Destruktor
Hashtable::~Hashtable()
{
	delete[] hTable;
}

// Hashfunktion aus erstem Uebungsblatt
int Hashtable::hashIndex(string name)
{
	// Zahl wird recht gross
	unsigned long long index = 0;

	// lange des strings
	int len = name.length();

	for (int i = 0; i < len; i++)
	{
		// das erste 31 hoch (n-1), das letzte hoch 0
		index += name[i] * pow(31.0, len - 1 - i);
	}

	return index % 1019;
}

// ADD: Eine Aktie mit Namen, WKN und Kürzel wird hinzugefügt.
bool Hashtable::addAktie()
{
	if (anzahlAktien == 1019) {
		cout << "Tabelle ist voll." << endl;
		return false;
	}

	string name;
	string wkn;
	string kuerzel;
	int index;

	cout << "Name: " << endl;
	cin >> name;
	cout << "Kuerzel: " << endl;
	cin >> kuerzel;
	cout << "WKN: " << endl;
	cin >> wkn;

	// index aus namen hashen
	index = hashIndex(name);

	// falls die erste errechnete stelle gleich frei ist
	if (hTable[index] == nullptr)
	{
		hTable[index] = new Aktie(name, wkn, kuerzel);
		anzahlAktien++;
	}
	// sonst quadratische sondierung bis ein freies gefunden wird oder man am ende der table ankommt
	else
	{
		int i = 0;
		// schleide unterbrochen sobald erfolgreich oder sobals index zu gross
		while (!(hTable[index] == nullptr) && index < 1019)
		{
			// i nach berechnung direkt erhoeht
			index += pow(i++, 2);
		}
		if (index < 1019) {
			hTable[index] = new Aktie(name, wkn, kuerzel);
			anzahlAktien++;
		}
		else
		{
			return false;
		}

	}

	return true;
}

// DEL: Aktie wird gelöscht.
bool Hashtable::delAktie()
{
	string name;
	cout << "Welche Aktie? Bitte name: " << endl;
	cin >> name;

	// mit namen mittels Search suchen und Index zurueckgeben
	int index = searchAktieIndex(name);

	//es kommt-1 falls es die Aktie nicht gibt, alles >-1 ist also "gefunden"
	if (index > (-1))
	{
		delete hTable[index];
		hTable[index] = nullptr;
		anzahlAktien--;
		return true;
	}
	else
	{
		cout << "Es gibt keine Aktie mit dem Namen " << name << endl;
		return false;
	}
}

// SEARCH: Eine Aktie wird in der Hashtabelle gesucht (Eingabe von Namen oder Kürzel) und der aktuellste Kurseintrag (Date,Open,High,Low,Close,Volume,Adj Close) wird ausgegeben.
bool Hashtable::searchAktie()
{
	string name;
	cout << "Suche nach Aktie. Welche Aktie? Bitte Name: " << endl;
	cin >> name;

	// mit namen mittels Search suchen und Index zurueckgeben
	int index = searchAktieIndex(name);

	//es kommt-1 falls es die Aktie nicht gibt, alles >-1 ist also "gefunden"
	if (index > (-1))
	{
		// untersten, also neuesten Eintrag ausgeben
		cout << "Aktie: " << hTable[index]->getName() << "(Kuerzel: " << hTable[index]->getKuerzel() << ", WKN: " << hTable[index]->getWKN() << endl;
		cout << hTable[index]->getDate(29) << " " << hTable[index]->getOpen(29) << " " << hTable[index]->getHigh(29) << " " << hTable[index]->getLow(29) << " " << hTable[index]->getClose(29) << " " << hTable[index]->getAdjClose(29) << " " << hTable[index]->getVolume(29) << endl;
		return true;
	}
	else
	{
		cout << "Es gibt keine Aktie mit dem Namen " << name << endl;
		return false;
	}


}

// Eine Aktie wird in der Hashtabelle gesucht mittels Namen und Index wird zurueckgegeben.
int Hashtable::searchAktieIndex(string name)
{
	// Index aus Namen hashen
	int index = hashIndex(name);
	string cmp;
	int i = 0;

	// da wegen quadratischer sondierung der wert irgendwo anders stehen koennte wird der wert zuerst am erst errechneten Index gesucht
	// und danach mittels qadratischer sondierung an den naechsten stellen wo es haette gespeichert werden koenen gesucht
	while (index < 1019) {
		//stelle koennte auch wieder geloescht werden sein, deshalb wird an alles Stellen nachgeschaut
		if (hTable[index] != nullptr) {
			cmp = hTable[index]->getName();
			if (cmp == name)
			{
				return index;
			}
		}
		index += pow(i++, 2);
	}

	return -1;
}


// SAVE <filename>: Programm speichert die Hashtabelle in eine Datei ab
bool Hashtable::saveHashtableTo() {

	cout << "Hashtabelle wird gepeichert! In welchem File? Bitte Name: ";
	string name;
	cin >> name;
	// richtige Endung anfuegen
	name += ".txt";
	int index = 0;

	ofstream myFile(name);
	myFile << "Hash Table" << endl;
	myFile << "--------------------------" << endl;

	if (!myFile.is_open()) {
		cerr << "Error" << endl;
		return false;
	}

	// jeder Eintrag wird geckeched
	while (index < 1019) {
		// falls ein Eintrag exisitert, wird zuerst der Index reingeschrieben in dem es gepeichert sind und dann alle Daten
		// teilweise mit Beistrichen und teilweise durch endl getrennt
		if (hTable[index] != nullptr) {
			myFile << index << "," << hTable[index]->getName() << "," << hTable[index]->getWKN() << "," << hTable[index]->getKuerzel() << endl;
			for (int i = 0; i < 30; i++)
			{
				myFile << hTable[index]->getDate(i) << "," << hTable[index]->getOpen(i) << "," << hTable[index]->getHigh(i) << "," << hTable[index]->getLow(i) << "," << hTable[index]->getClose(i) << "," << hTable[index]->getAdjClose(i) << "," << hTable[index]->getVolume(i) << endl;
			}
		}
		index++;
	}

	myFile.close();
	return true;
}

// LOAD <filename>: Programm lädt die Hashtabelle aus einer Datei
bool Hashtable::loadHashtableFrom()
{

	cout << "Hashtabelle wird geladen! Aus welchem File? Bitte Name: ";
	string filename;
	cin >> filename;
	filename += ".txt";

	// helfer
	string index_read, name_read, wkn_read, kuerzel_read, date_read, open_read, high_read, low_read, close_read, adjClose_read, volume_read;
	int index;

	ifstream csvread(filename);


	if (!csvread.is_open()) {
		cerr << "Error" << endl;
		return false;
	}

	// die ersten 2 Zeilen ignorieren
	csvread.ignore(500, '\n');
	csvread.ignore(500, '\n');

	while (!csvread.eof()) {
		// zuerst Index, Name und WKN lesen
		getline(csvread, index_read, ',');
		getline(csvread, name_read, ',');
		getline(csvread, wkn_read, ',');
		getline(csvread, kuerzel_read, '\n');

		// falls eigentlich leere Zeile / letzte Zeile
		if (index_read.length() == 0) {
			continue;
		}

		// Index zu double converten
		index = atof(index_read.c_str());
		// neue Aktie in Hashtabelle erstellen mittels Konstruktor
		hTable[index] = new Aktie(name_read, wkn_read, kuerzel_read);

		// die Kurswerte einlesen und converten und speichern
		for (int i = 0; i < 30; i++) {
			getline(csvread, date_read, ',');
			getline(csvread, open_read, ',');
			getline(csvread, high_read, ',');
			getline(csvread, low_read, ',');
			getline(csvread, close_read, ',');
			getline(csvread, adjClose_read, ',');
			getline(csvread, volume_read, '\n');
			//save
			hTable[index]->setDate(i, date_read);
			hTable[index]->setOpen(i, atof(open_read.c_str()));
			hTable[index]->setHigh(i, atof(high_read.c_str()));
			hTable[index]->setLow(i, atof(low_read.c_str()));
			hTable[index]->setClose(i, atof(close_read.c_str()));
			hTable[index]->setAdjClose(i, atof(adjClose_read.c_str()));
			hTable[index]->setVolume(i, atof(volume_read.c_str()));
		}

	}

	csvread.close();
	return true;
}

// PLOT: Die Schlusskurse der letzten 30 Tage einer Aktie werden als ASCII Grafik ausgegeben, Format ist frei wählbar.
bool Hashtable::plotAktie()
{
	cout << "Welche Aktie wollen Sie plotten?" << endl;
	string aktienname;
	cin >> aktienname;

	int index = searchAktieIndex(aktienname);

	if (index > (-1))
	{
		hTable[index]->plotAktie();
	}
	else
	{
		cout << "Es gibt keine Aktie mit dem Namen " << aktienname << endl;
		return false;
	}
	return true;
}

// IMPORT: Kurswerte für eine Aktie werden aus einer csv Datei importiert
bool Hashtable::importAktie()
{
	cout << "In welche Aktie? Name:" << endl;
	string aktiename;
	cin >> aktiename;

	// es wird nach der Aktie gesucht, in die die Daten geladen werden sollen
	int index = searchAktieIndex(aktiename);

	if (index > (-1))
	{
		// eigentliche Funktion in Klasse Aktie, gibt bei Erofl true zurueck, sonst false
		return hTable[index]->importAktie();
	}
	else
	{
		cout << "Es gibt keine Aktie mit dem Namen " << aktiename << endl;
		return false;
	}
}
