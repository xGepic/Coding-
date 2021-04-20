#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Aktie.h"

class Hashtable
{
public:
	Hashtable();
	virtual ~Hashtable();

	bool addAktie();
	int hashIndex(string name);
	bool delAktie();
	bool searchAktie();
	int searchAktieIndex(string name);
	bool saveHashtableTo();
	bool loadHashtableFrom();
	bool plotAktie();
	bool importAktie();

protected:

private:
	int anzahlAktien;
	bool* isFree;
	Aktie** hTable;
};

#endif // HASHTABLE_H
