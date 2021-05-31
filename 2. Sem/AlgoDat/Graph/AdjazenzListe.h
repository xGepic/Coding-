#ifndef ADJAZENZLISTE_H
#define ADJAZENZLISTE_H
#include <iostream>
#include <string>

using namespace std;

class AdjazenzListe {

public:

	AdjazenzListe(string station, int kosten, string linie);
	virtual ~AdjazenzListe();

	string getStation();
	string getLinie();
	int getKosten();
	int getAnzNachbarn();
	void incAnzNachbarn();

	// ob sich eine Station mit dem Stationsnamen in der Liste befindet
	bool inListe(string name);
	void addNeighbour(string stationN, int kostenN, string linieN);
	AdjazenzListe* addToListe(AdjazenzListe* root, string stationN, int kostenN, string linieN);
	AdjazenzListe* findInListe(string name);

	string station;
	string linie;

	// kosten von vorgänger zu nachber, 0 falls anfangsknoten
	int kosten;
	// anzahl der knoten in nachbar liste
	int anzahlNachbarn;
	// nachbar knoten, stationen die über den aktuellen knoten erreichbar sind
	AdjazenzListe* nachbar;
	// nächster knoten in adjazenzliste
	AdjazenzListe* next;

protected:


private:


};
#endif // ADJAZENZLISTE_H