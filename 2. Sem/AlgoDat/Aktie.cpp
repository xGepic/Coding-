#include "Aktie.h"
#include <iostream>
#include <string>
#include <algorithm>

// Default Konstruktor
Aktie::Aktie()
{
	name = "";
	wkn = "";
	kuerzel = "";
}

// Konstruktor
Aktie::Aktie(string name, string wkn, string kuerzel)
{
	this->name = name;
	this->wkn = wkn;
	this->kuerzel = kuerzel;

	date = new string[30];
	open = new double[30];
	high = new double[30];
	low = new double[30];
	close = new double[30];
	adj_close = new double[30];
	volume = new long int[30];
	for (int i = 0; i < 30; i++)
	{
		date[i] = "nodate";
		open[i] = -1;
		high[i] = -1;
		low[i] = -1;
		close[i] = -1;
		adj_close[i] = -1;
		volume[i] = -1;
	}
}

// Destruktor
Aktie::~Aktie()
{
	delete[] date;
	delete[] open;
	delete[] high;
	delete[] low;
	delete[] close;
	delete[] adj_close;
	delete[] volume;
}

// Getter
string Aktie::getName()
{
	return this->name;
}
string Aktie::getWKN()
{
	return this->wkn;
}
string Aktie::getKuerzel()
{
	return this->kuerzel;
}
string Aktie::getDate(int n)
{
	return this->date[n];
}
double Aktie::getOpen(int n)
{
	return this->open[n];
}
double Aktie::getHigh(int n)
{
	return this->high[n];
}
double Aktie::getLow(int n)
{
	return this->low[n];
}
double Aktie::getClose(int n)
{
	return this->close[n];
}
double Aktie::getAdjClose(int n)
{
	return this->adj_close[n];
}
long int Aktie::getVolume(int n)
{
	return this->volume[n];
}
// Setter
void Aktie::setName(string newName) {
	name = newName;
}
void Aktie::setWKN(string newWkn) {
	wkn = newWkn;
}
void Aktie::setKuerzel(string newKuerzel)
{
	kuerzel = newKuerzel;
}
void Aktie::setDate(int n, string content)
{
	this->date[n] = content;
}
void Aktie::setOpen(int n, double content)
{
	this->open[n] = content;
}
void Aktie::setHigh(int n, double content)
{
	this->high[n] = content;
}
void Aktie::setLow(int n, double content)
{
	this->low[n] = content;
}
void Aktie::setClose(int n, double content)
{
	this->close[n] = content;
}
void Aktie::setAdjClose(int n, double content)
{
	this->adj_close[n] = content;
}
void Aktie::setVolume(int n, long int content)
{
	this->volume[n] = content;
}

// PLOT: Die Schlusskurse der letzten 30 Tage einer Aktie werden als ASCII Grafik ausgegeben, Format ist frei wählbar.
bool Aktie::plotAktie() {

	cout << endl;
	// links die Zahlen, die aelteren zuerst
	for (int i = 1; i < 31; i++) {
		if (i < 10) {
			// 0 davor wegen uniformitaet
			cout << 0;
		}
		cout << i << ".";
		// value printen
		printValue(this->getAdjClose(i - 1));
	}
	cout << endl;
	return true;
}

//  gibt Pfeil mit relativer laenge aus  fuer den Wert
void Aktie::printValue(double value) {

	int temp = value / 100;
	value -= (temp * 100.0);

	for (int i = 0; i < value; i++) {
		cout << "-";
	}
	cout << ">";
	cout << endl;
}

// IMPORT: Kurswerte für eine Aktie werden aus einer csv Datei importiert
bool Aktie::importAktie() {
	string eineAktie[30];

	string filename = "";
	cout << "Which file would you like to import? Name:" << endl;
	cin >> filename;
	filename += ".csv";

	string date_read, open_read, high_read, low_read, close_read, adjClose_read, volume_read;

	ifstream csvread(filename);
	int a = 0;

	if (!csvread.is_open()) {
		cerr << "Error" << endl;
		return false;
	}

	// Zeilen werden gezahlt, wollen nur die neuesten 30
	ifstream inFile(filename);
	int size = static_cast<int>(count(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>(), '\n'));
	inFile.close();

	// die, die nicht gebraucht werden, ignorieren
	for (int i = 1; i < size - 28; i++) {
		csvread.ignore(500, '\n');
	}

	// die letzten 30 Eintraege lesen
	while (!csvread.eof()) {
		if (a > 29) {
			break;
		}
		getline(csvread, date_read, ',');
		getline(csvread, open_read, ',');
		getline(csvread, high_read, ',');
		getline(csvread, low_read, ',');
		getline(csvread, close_read, ',');
		getline(csvread, adjClose_read, ',');
		getline(csvread, volume_read, '\n');

		this->date[a] = date_read;
		this->open[a] = atof(open_read.c_str());
		this->high[a] = atof(high_read.c_str());
		this->low[a] = atof(low_read.c_str());
		this->close[a] = atof(close_read.c_str());
		this->adj_close[a] = atof(adjClose_read.c_str());
		this->volume[a] = atof(volume_read.c_str());

		a++;
	}
	csvread.close();
	return true;
}
