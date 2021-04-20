#ifndef AKTIE_H
#define AKTIE_H
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
using namespace std;


class Aktie
{
public:
	Aktie();
	Aktie(string name, string wkn, string kuerzel);
	virtual ~Aktie();

	bool plotAktie();
	bool importAktie();
	void printValue(double value);

	string getName();
	string getWKN();
	string getKuerzel();
	string getDate(int n);
	double getOpen(int n);
	double getHigh(int n);
	double getLow(int n);
	double getClose(int n);
	double getAdjClose(int n);
	long int getVolume(int n);

	void setDate(int n, string content);
	void setOpen(int n, double content);
	void setHigh(int n, double content);
	void setLow(int n, double content);
	void setClose(int n, double content);
	void setAdjClose(int n, double content);
	void setVolume(int n, long int content);

protected:

private:
	string name;
	string wkn;
	string kuerzel; string* date;
	double* open;
	double* high;
	double* low;
	double* close;
	double* adj_close;
	long int* volume;

	void setName(string newName);
	void setWKN(string newWkn);
	void setKuerzel(string newKuerzel);
};

#endif // AKTIE_H
